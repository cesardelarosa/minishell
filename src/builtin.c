/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <cde-la-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 09:20:41 by cde-la-r          #+#    #+#             */
/*   Updated: 2024/09/26 15:25:12 by cde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "libft.h"
#include "minishell.h"

/* 
** Changes the current working directory to the one specified in args[1].
** If no directory is provided, it prints an error message.
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
** Echoes the given arguments to standard output.
** If "-n" is passed as the first argument, it suppresses the newline.
*/
void	builtin_echo(char **args)
{
	int	newline;
	int	i;

	newline = !args[1] || ft_strncmp(args[1], "-n", 3);
	i = 2 - newline;
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[++i])
			printf(" ");
	}
	if (newline)
		printf("\n");
}

/* 
** Exits the shell with the specified exit status.
** If no status is provided, it exits with status 0.
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
