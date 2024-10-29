/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tu_nombre <tu_email@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 13:45:46 by tu_nombre         #+#    #+#             */
/*   Updated: 2024/10/29 17:00:00 by tu_nombre        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include "operators.h"
#include "builtins.h"

char	*which(const char *cmd)
{
	char	*path;
	char	*dir;
	char	*full_path;
	size_t	cmd_len;

	path = getenv("PATH");
	cmd_len = ft_strlen(cmd);
	while (path && *path)
	{
		dir = (char *)path;
		while (*path && *path != ':')
			path++;
		full_path = malloc((path - dir) + cmd_len + 2);
		if (full_path == NULL)
			return (NULL);
		ft_memcpy(full_path, dir, path - dir);
		full_path[path - dir] = '/';
		ft_memcpy(full_path + (path - dir) + 1, cmd, cmd_len);
		full_path[(path - dir) + cmd_len + 1] = '\0';
		if (access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
		if (*path == ':')
			path++;
	}
	return (NULL);
}

int	handle_builtin(t_command cmd)
{
	if (!ft_strcmp(cmd.args[0], "cd"))
		builtin_cd(cmd.args);
	else if (!ft_strcmp(cmd.args[0], "pwd"))
		builtin_pwd();
	else if (!ft_strcmp(cmd.args[0], "echo"))
		builtin_echo(cmd.args);
	else if (!ft_strcmp(cmd.args[0], "exit"))
		builtin_exit(cmd.args);
	else if (!ft_strcmp(cmd.args[0], "export"))
		builtin_export(cmd.args, cmd.envp);
	else if (!ft_strcmp(cmd.args[0], "unset"))
		builtin_unset(cmd.args);
	else if (!ft_strcmp(cmd.args[0], "env"))
		builtin_env(cmd.envp);
	else
		return (0);
	return (1);
}

void	execute_builtin(t_command cmd)
{
	int	saved_stdin;
	int	saved_stdout;

	saved_stdin = -1;
	saved_stdout = -1;
	if (cmd.input.fd != -1)
	{
		saved_stdin = dup(STDIN_FILENO);
		dup2(cmd.input.fd, STDIN_FILENO);
		close(cmd.input.fd);
	}
	if (cmd.output.fd != -1)
	{
		saved_stdout = dup(STDOUT_FILENO);
		dup2(cmd.output.fd, STDOUT_FILENO);
		close(cmd.output.fd);
	}
	handle_builtin(cmd);
	if (saved_stdin != -1)
	{
		dup2(saved_stdin, STDIN_FILENO);
		close(saved_stdin);
	}
	if (saved_stdout != -1)
	{
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdout);
	}
}

void	execute_external(t_command cmd)
{
	char	*exec_path;

	if (cmd.input.fd != -1)
	{
		if (dup2(cmd.input.fd, STDIN_FILENO) == -1)
		{
			perror("dup2 input failed");
			exit(EXIT_FAILURE);
		}
		close(cmd.input.fd);
	}
	if (cmd.output.fd != -1)
	{
		if (dup2(cmd.output.fd, STDOUT_FILENO) == -1)
		{
			perror("dup2 output failed");
			exit(EXIT_FAILURE);
		}
		close(cmd.output.fd);
	}
	if (access(cmd.args[0], X_OK) == 0)
	{
		execve(cmd.args[0], cmd.args, cmd.envp);
		perror("execve failed");
		exit(EXIT_FAILURE);
	}
	else
	{
		exec_path = which(cmd.args[0]);
		if (exec_path != NULL)
		{
			execve(exec_path, cmd.args, cmd.envp);
			perror("execve failed");
			free(exec_path);
			exit(EXIT_FAILURE);
		}
		else
		{
			fprintf(stderr, "minishell: %s: command not found\n", cmd.args[0]);
			exit(EXIT_FAILURE);
		}
	}
}

void	handle_command(t_command cmd)
{
	pid_t	pid;
	int		status;

	if (cmd.args == NULL || cmd.args[0] == NULL)
		return ;
	if (handle_builtin(cmd) == 1)
		execute_builtin(cmd);
	else
	{
		pid = fork();
		if (pid == 0)
			execute_external(cmd);
		else if (pid < 0)
			perror("minishell: fork error");
		else
		{
			if (waitpid(pid, &status, 0) == -1)
				perror("minishell: waitpid error");
			if (WIFEXITED(status))
				g_exit_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				g_exit_status = 128 + WTERMSIG(status);
		}
	}
}

void	handle_or(t_operator op)
{
	exec(op.left);
	if (g_exit_status != 0)
		exec(op.right);
}

void	handle_and(t_operator op)
{
	exec(op.left);
	if (g_exit_status == 0)
		exec(op.right);
}

void	handle_pipe(t_operator op)
{
	int		fd[2];
	pid_t	pid_left;
	pid_t	pid_right;
	int		status_left;
	int		status_right;

	if (pipe(fd) == -1)
	{
		perror("pipe");
		return ;
	}
	pid_left = fork();
	if (pid_left == -1)
	{
		perror("fork");
		return ;
	}
	if (pid_left == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		exec(op.left);
		exit(g_exit_status);
	}
	pid_right = fork();
	if (pid_right == -1)
	{
		perror("fork");
		return ;
	}
	if (pid_right == 0)
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		exec(op.right);
		exit(g_exit_status);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(pid_left, &status_left, 0);
	waitpid(pid_right, &status_right, 0);
	g_exit_status = WEXITSTATUS(status_right);
}

void	exec(t_ast_node *node)
{
	if (node == NULL)
		return ;
	print_node(node);
	if (node->type == COMMAND)
		handle_command(node->u_data.cmd);
	else if (node->type == OPERATOR)
	{
		if (node->u_data.op.type == PIPE)
			handle_pipe(node->u_data.op);
		else if (node->u_data.op.type == AND)
			handle_and(node->u_data.op);
		else if (node->u_data.op.type == OR)
			handle_or(node->u_data.op);
		else
			perror("minishell: unsupported operator");
	}
	else
		perror("minishell: unsupported node type");
	free_node(node);
}
