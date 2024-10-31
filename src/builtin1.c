/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <cde-la-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 09:20:41 by cde-la-r          #+#    #+#             */
/*   Updated: 2024/10/31 01:21:18 by cde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "libft.h"
#include "minishell.h"

/*
** Changes the current working directory to the one specified in args[1].
** If no directory is provided or if chdir fails, it prints an error message
** and sets g_exit_status accordingly.
**
** @param args: The arguments passed to the cd command.
**              args[1] should contain the target directory.
*/
void	builtin_cd(char **args)
{
	if (!args[1])
	{
		ft_putstr_fd("minishell: cd: expected argument\n", STDERR_FILENO);
		g_exit_status = 1;
	}
	else if (chdir(args[1]) != 0)
	{
		perror("minishell: cd");
		g_exit_status = 1;
	}
	else
		g_exit_status = 0;
}

/*
** Prints the current working directory to standard output.
** If an error occurs, it prints an error message and sets g_exit_status.
*/
void	builtin_pwd(void)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		ft_putstr_fd(cwd, STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		g_exit_status = 0;
	}
	else
	{
		perror("minishell: pwd");
		g_exit_status = 1;
	}
}

/*
** Checks if the given argument is the '-n' flag for echo.
**
** @param arg: The argument to check.
**
** @return: 1 if the argument is a valid '-n' flag, 0 otherwise.
*/
int	is_flag_n(char *arg)
{
	int	i;

	i = 1;
	if (arg[0] != '-')
		return (0);
	while (arg[i] == 'n')
		i++;
	return (arg[i] == '\0');
}

/*
** Echoes the given arguments to standard output.
** If "-n" is passed as the first argument(s), it suppresses the newline.
** Sets g_exit_status to 0 upon successful execution.
**
** @param args: The arguments to echo.
**              args[1] may be "-n" to suppress the newline.
*/
void	builtin_echo(char **args)
{
	int	newline;

	newline = 1;
	while (args[1] && is_flag_n(args[1]))
	{
		newline = 0;
		args++;
	}
	while (*++args)
	{
		ft_putstr_fd(*args, STDOUT_FILENO);
		if (*(args + 1))
			ft_putstr_fd(" ", STDOUT_FILENO);
	}
	if (newline)
		ft_putstr_fd("\n", STDOUT_FILENO);
	g_exit_status = 0;
}

/*
** Exits the shell with the specified exit status.
** If no status is provided, it exits with status 0.
** Before exiting, it sets g_exit_status to the exit status.
**
** @param args: The arguments passed to the exit command.
**              args[1] may contain the exit status.
*/
void	builtin_exit(char **args)
{
	int	exit_status;

	exit_status = 0;
	if (args[1])
	{
		exit_status = ft_atoi(args[1]);
		if (exit_status < 0)
			exit_status = 255;
	}
	g_exit_status = exit_status;
	ft_putstr_fd("Exiting minishell...\n", STDOUT_FILENO);
	ft_free_split(args);
	exit(exit_status);
}
