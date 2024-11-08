/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 13:02:35 by cde-la-r          #+#    #+#             */
/*   Updated: 2024/10/31 01:05:18 by cde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include "libft.h"
#include "minishell.h"
#include "operators.h"
#include "builtins.h"

int	setup_input_redirection(t_command *cmd, int *stdin_copy)
{
	if (cmd->input.fd != -1)
	{
		if (stdin_copy != NULL)
		{
			*stdin_copy = dup(STDIN_FILENO);
			if (*stdin_copy == -1)
			{
				perror("dup stdin");
				return (-1);
			}
		}
		if (dup2(cmd->input.fd, STDIN_FILENO) == -1)
		{
			perror("dup2 input");
			if (stdin_copy != NULL && *stdin_copy != -1)
				close(*stdin_copy);
			return (-1);
		}
		close(cmd->input.fd);
		cmd->input.fd = -1;
	}
	return (0);
}

int	setup_output_redirection(t_command *cmd, int *stdout_copy)
{
	if (cmd->output.fd != -1)
	{
		if (stdout_copy != NULL)
		{
			*stdout_copy = dup(STDOUT_FILENO);
			if (*stdout_copy == -1)
			{
				perror("dup stdout");
				return (-1);
			}
		}
		if (dup2(cmd->output.fd, STDOUT_FILENO) == -1)
		{
			perror("dup2 output");
			if (stdout_copy != NULL && *stdout_copy != -1)
				close(*stdout_copy);
			return (-1);
		}
		close(cmd->output.fd);
		cmd->output.fd = -1;
	}
	return (0);
}

int	setup_redirections(t_command *cmd, int *stdin_copy, int *stdout_copy)
{
	if (stdin_copy != NULL)
		*stdin_copy = -1;
	if (stdout_copy != NULL)
		*stdout_copy = -1;
	if (setup_input_redirection(cmd, stdin_copy) == -1)
		return (-1);
	if (setup_output_redirection(cmd, stdout_copy) == -1)
	{
		if (stdin_copy != NULL && *stdin_copy != -1)
		{
			dup2(*stdin_copy, STDIN_FILENO);
			close(*stdin_copy);
		}
		return (-1);
	}
	return (0);
}

void	reset_redirections(int stdin_copy, int stdout_copy)
{
	if (stdin_copy != -1)
	{
		dup2(stdin_copy, STDIN_FILENO);
		close(stdin_copy);
	}
	if (stdout_copy != -1)
	{
		dup2(stdout_copy, STDOUT_FILENO);
		close(stdout_copy);
	}
}

t_builtin	is_builtin(char *cmd)
{
	if (ft_strcmp(cmd, "cd") == 0)
		return (BUILTIN_CD);
	else if (ft_strcmp(cmd, "pwd") == 0)
		return (BUILTIN_PWD);
	else if (ft_strcmp(cmd, "echo") == 0)
		return (BUILTIN_ECHO);
	else if (ft_strcmp(cmd, "exit") == 0)
		return (BUILTIN_EXIT);
	else if (ft_strcmp(cmd, "export") == 0)
		return (BUILTIN_EXPORT);
	else if (ft_strcmp(cmd, "unset") == 0)
		return (BUILTIN_UNSET);
	else if (ft_strcmp(cmd, "env") == 0)
		return (BUILTIN_ENV);
	return (BUILTIN_NONE);
}

void	execute_builtin(t_builtin builtin, t_command *cmd)
{
	int	stdin_copy;
	int	stdout_copy;

	if (setup_redirections(cmd, &stdin_copy, &stdout_copy) == -1)
	{
		g_exit_status = 1;
		return ;
	}
	if (builtin == BUILTIN_CD)
		builtin_cd(cmd->args);
	else if (builtin == BUILTIN_PWD)
		builtin_pwd();
	else if (builtin == BUILTIN_ECHO)
		builtin_echo(cmd->args);
	else if (builtin == BUILTIN_EXIT)
		builtin_exit(cmd->args);
	else if (builtin == BUILTIN_EXPORT)
		builtin_export(cmd->args, cmd->envp);
	else if (builtin == BUILTIN_UNSET)
		builtin_unset(cmd->args);
	else if (builtin == BUILTIN_ENV)
		builtin_env(cmd->envp);
	reset_redirections(stdin_copy, stdout_copy);
}

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

void	execute_external(t_command *cmd)
{
	char	*exec_path;

	if (cmd->args[0] == NULL)
		exit(EXIT_FAILURE);
	if (access(cmd->args[0], X_OK) == 0)
		exec_path = cmd->args[0];
	else
		exec_path = which(cmd->args[0]);
	if (exec_path == NULL)
	{
		perror("minishell: command not found");
		exit(EXIT_FAILURE);
	}
	if (execve(exec_path, cmd->args, cmd->envp) == -1)
	{
		perror("execve failed");
		exit(EXIT_FAILURE);
	}
}

void	execute_external_command(t_command *cmd)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		if (setup_redirections(cmd, NULL, NULL) == -1)
			exit(EXIT_FAILURE);
		execute_external(cmd);
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
	{
		perror("minishell: fork error");
		g_exit_status = 1;
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			g_exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			g_exit_status = 128 + WTERMSIG(status);
	}
}

void	handle_command(t_command *cmd)
{
	t_builtin	builtin;

	if (cmd->args[0] == NULL)
		return ;
	builtin = is_builtin(cmd->args[0]);
	if (builtin != BUILTIN_NONE)
		execute_builtin(builtin, cmd);
	else
		execute_external_command(cmd);
}

void	exec(t_ast_node *node)
{
	if (node == NULL)
		return ;
	if (node->type == COMMAND)
		handle_command(&node->u_data.cmd);
	else if (node->type == OPERATOR)
	{
		if (node->u_data.op.type == PIPE)
			handle_pipe(node->u_data.op);
		else if (node->u_data.op.type == AND)
			handle_and(node->u_data.op);
		else if (node->u_data.op.type == OR)
			handle_or(node->u_data.op);
		else
			perror("unsupported operator");
	}
	else
		perror("unsupported node type");
}
