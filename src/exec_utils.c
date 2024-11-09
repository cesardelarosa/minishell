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

int	setup_single_redir(int *fd, int fileno, int *copy)
{
	if (*fd == -1)
		return (0);
	if (copy != NULL)
	{
		*copy = dup(fileno);
		if (*copy == -1)
		{
			perror("dup");
			return (-1);
		}
	}
	if (dup2(*fd, fileno) == -1)
	{
		perror("dup2");
		if (copy != NULL && *copy != -1)
			close(*copy);
		return (-1);
	}
	close(*fd);
	*fd = -1;
	return (0);
}

int	setup_redir(t_command *cmd, int *stdin_copy, int *stdout_copy)
{
	if (stdin_copy != NULL)
		*stdin_copy = -1;
	if (stdout_copy != NULL)
		*stdout_copy = -1;
	if (setup_single_redir(&cmd->input.fd, STDIN_FILENO, stdin_copy) == -1)
		return (-1);
	if (setup_single_redir(&cmd->output.fd, STDOUT_FILENO, stdout_copy) == -1)
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

	if (setup_redir(cmd, &stdin_copy, &stdout_copy) == -1)
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
