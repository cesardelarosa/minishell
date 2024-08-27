/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <cde-la-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 09:20:41 by cde-la-r          #+#    #+#             */
/*   Updated: 2024/08/27 09:20:43 by cde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "libft.h"
#include "minishell.h"

void	builtin_cd(char **args)
{
	if (args[1] == NULL)
		fprintf(stderr, "minishell: expected argument to \"cd\"\n");
	else
	{
		if (chdir(args[1]) != 0)
			perror("minishell");
	}
}

void	builtin_pwd(void)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		printf("%s\n", cwd);
	else
		perror("minishell");
}

void	builtin_echo(char **args)
{
	int	newline;
	int	i;

	newline = 1;
	i = 1;
	if (args[1] && strcmp(args[1], "-n") == 0)
	{
		newline = 0;
		i++;
	}
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
}

void	builtin_exit(char **args)
{
	int	exit_status;

	exit_status = 0;
	if (args[1] != NULL)
		exit_status = ft_atoi(args[1]);
	printf("Exiting minishell...\n");
	ft_free_split(args);
	exit(exit_status);
}

int	handle_builtin(char **args)
{
	if (!strcmp(args[0], "cd"))
		builtin_cd(args);
	else if (!strcmp(args[0], "pwd"))
		builtin_pwd();
	else if (!strcmp(args[0], "echo"))
		builtin_echo(args);
	else if (!strcmp(args[0], "exit"))
		builtin_exit(args);
	else
		return (0);
	return (1);
}
