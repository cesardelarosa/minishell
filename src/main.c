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
	perror("minishell");
	exit(EXIT_FAILURE);
}

void	execute_command(char **args)
{
	pid_t	pid;
	int		status;

	if (handle_builtin(args) == 0)
	{
		pid = fork();
		if (pid == 0)
			handle_extern(args);
		else if (pid < 0)
			perror("minishell");
		waitpid(pid, &status, 0);
	}
}

void	handle_command(char **args)
{
	if (args != NULL && args[0] != NULL)
		execute_command(args);
	ft_free_split(args);
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

void	setup_signal_handlers(void)
{
	signal(SIGINT, sigquit_handler);
	signal(SIGQUIT, SIG_IGN);
}

char	*read_input(void)
{
	char	*input;

	input = readline("minishell> ");
	if (input == NULL)
		exit(EXIT_SUCCESS);
	if (ft_strlen(input) > 0)
		add_history(input);
	return (input);
}

char	**parse_command(char *input)
{
	char	**args;

	args = ft_split(input, ' ');
	free(input);
	return (args);
}

int	main(void)
{
	setup_signal_handlers();
	while (1)
		handle_command(parse_command(read_input()));
	return (0);
}
