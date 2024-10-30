/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 13:02:35 by cde-la-r          #+#    #+#             */
/*   Updated: 2024/10/30 13:02:40 by cde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include "libft.h"

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

int	setup_redirections(t_command *cmd)
{
	if (cmd->input.fd != -1)
	{
		if (dup2(cmd->input.fd, STDIN_FILENO) == -1)
		{
			perror("dup2 input");
			return (-1);
		}
		close(cmd->input.fd);
	}
	if (cmd->output.fd != -1)
	{
		if (dup2(cmd->output.fd, STDOUT_FILENO) == -1)
		{
			perror("dup2 output");
			return (-1);
		}
		close(cmd->output.fd);
	}
	return (0);
}

void	execute_external(t_command *cmd)
{
	char	*exec_path;

	if (cmd->args[0] == NULL)
		return ;
	if (access(cmd->args[0], X_OK) == 0)
		exec_path = cmd->args[0];
	else
		exec_path = which(cmd->args[0]);
	if (exec_path == NULL)
	{
		perror("minishell: command not found");
		return ;
	}
	if (setup_redirections(cmd) == -1)
		exit(EXIT_FAILURE);
	execve(exec_path, cmd->args, cmd->envp);
	perror("execve failed");
	exit(EXIT_FAILURE);
}

void	handle_command(t_command *cmd)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
		execute_external(cmd);
	else if (pid < 0)
		perror("minishell: fork error");
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			g_exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			g_exit_status = 128 + WTERMSIG(status);
	}
}

void	exec(t_ast_node *node)
{
	if (node == NULL)
		return ;
	if (node->type == COMMAND)
		handle_command(&node->u_data.cmd);
	free_node(node);
}
