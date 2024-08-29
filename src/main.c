/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <cde-la-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 17:48:49 by cde-la-r          #+#    #+#             */
/*   Updated: 2024/08/27 17:48:50 by cde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <dirent.h>
#include <signal.h>
#include <readline/history.h>
#include <readline/readline.h>
#include "libft.h"
#include "minishell.h"

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

void	execute_command(char **args)
{
	pid_t	pid;
	int		status;
	char	*exec_path;

	if (handle_builtin(args) == 0)
	{
		pid = fork();
		if (pid == 0)
		{
			if (access(args[0], X_OK) == 0)
				execve(args[0], args, environ);
			exec_path = which(args[0]);
			if (exec_path != NULL)
				execve(exec_path, args, environ);
			free(exec_path);
			perror("minishell");
			exit(EXIT_FAILURE);
		}
		else if (pid < 0)
			perror("minishell");
		waitpid(pid, &status, 0);
	}
}

void	sigquit_handler(int sign)
{
	if (sign == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

int	main(void)
{
	char	*input;
	char	**args;

	signal(SIGINT, sigquit_handler);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		input = readline("minishell> ");
		if (input == NULL)
			break ;
		if (ft_strlen(input) > 0)
			add_history(input);
		args = ft_split(input, ' ');
		free(input);
		if (args == NULL || args[0] == NULL)
		{
			ft_free_split(args);
			continue ;
		}
		execute_command(args);
		ft_free_split(args);
	}
	return (0);
}
