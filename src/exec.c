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

int			setup_single_redir(int *fd, int fileno, int *copy);
int			setup_redir(t_command *cmd, int *stdin_copy, int *stdout_copy);
void		reset_redirections(int stdin_copy, int stdout_copy);
t_builtin	is_builtin(char *cmd);
void		execute_builtin(t_builtin builtin, t_command *cmd);

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
		path += *path == ':';
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
		if (setup_redir(cmd, NULL, NULL) == -1)
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
		node->u_data.op.left = NULL;
		node->u_data.op.right = NULL;
	}
	else
		perror("unsupported node type");
	free_node(node);
	node = NULL;
}
