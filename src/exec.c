/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <cde-la-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 13:45:46 by cde-la-r          #+#    #+#             */
/*   Updated: 2024/08/30 13:45:46 by cde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include "libft.h"
#include "minishell.h"
#include "builtins.h"

extern char				**environ;

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
		full_path = (char *)malloc((path - dir) + cmd_len + 2);
		if (full_path == NULL)
			return (NULL);
		ft_memcpy(full_path, dir, path - dir);
		full_path[path - dir] = '/';
		ft_memcpy(full_path + (path - dir) + 1, cmd, cmd_len);
		full_path[(path - dir) + cmd_len + 1] = '\0';
		if (access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
		path += *path != '\0';
	}
	return (NULL);
}

void	handle_extern(char **args)
{
	char	*exec_path;

	if (access(args[0], X_OK) == 0)
		execve(args[0], args, environ);
	else if (access(args[0], F_OK) != 0)
	{
		exec_path = which(args[0]);
		if (exec_path != NULL)
			execve(exec_path, args, environ);
		free(exec_path);
	}
	perror("minishell: execution failed");
	exit(EXIT_FAILURE);
}

int	handle_builtin(char **args)
{
	if (!ft_strncmp(args[0], "cd", 3))
		builtin_cd(args);
	else if (!ft_strncmp(args[0], "pwd", 4))
		builtin_pwd();
	else if (!ft_strncmp(args[0], "echo", 5))
		builtin_echo(args);
	else if (!ft_strncmp(args[0], "exit", 5))
		builtin_exit(args);
	else
		return (0);
	return (1);
}

void	handle_command(char **args)
{
	pid_t	pid;
	int		status;

	if (args == NULL)
		return ;
	if (args[0] != NULL && handle_builtin(args) == 0)
	{
		pid = fork();
		if (pid == 0)
			handle_extern(args);
		else if (pid < 0)
			perror("minishell: fork error");
		else if (waitpid(pid, &status, 0) == -1)
			perror("minishell: waitpid error");
	}
	ft_free_split(args);
}
