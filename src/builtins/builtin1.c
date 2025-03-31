/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrian <adrian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 09:20:41 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/03/30 13:15:08 by cesi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "libft.h"

/*
** Changes the current working directory to the one specified in args[1].
** If no directory is provided, it prints an error message.
**
** @param args: The arguments passed to the cd command.
**              args[1] should contain the target directory.
*/
void	builtin_cd(char **args)
{
	if (!args[1])
		perror("minishell: cd: expected argument");
	else if (chdir(args[1]))
		perror("minishell: cd: failed to change directory");
}

/*
** Prints the current working directory to standard output.
** If an error occurs, it prints an error message.
*/
void	builtin_pwd(void)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)))
		printf("%s\n", cwd);
	else
		perror("minishell: pwd: failed to get current directory");
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
//	g_exit_status = 0;
}

/*
** Exits the shell with the specified exit status.
** If no status is provided, it exits with status 0.
**
** @param args: The arguments passed to the exit command.
**              args[1] may contain the exit status.
*/
void	builtin_exit(char **args)
{
	int	exit_status;

	exit_status = 0;
	if (args[1])
		exit_status = ft_atoi(args[1]);
	printf("Exiting minishell...\n");
	ft_free_split(args);
	exit(exit_status);
}
