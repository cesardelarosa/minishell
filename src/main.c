/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <cde-la-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 20:11:43 by cde-la-r          #+#    #+#             */
/*   Updated: 2024/08/26 20:11:43 by cde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <unistd.h>
#include <sys/wait.h>
#include "libft.h"
#include "minishell.h"

void	execute_command(char **args)
{
	pid_t	pid;
	int		status;

	if (handle_builtin(args) == 0)
	{
		pid = fork();
		if (pid == 0)
		{
			if (execvp(args[0], args) == -1)
				perror("minishell");
			exit(EXIT_FAILURE);
		}
		else if (pid < 0)
			perror("minishell");
		else
			waitpid(pid, &status, 0);
	}
}

int	main(void)
{
	char	*input;
	char	**args;

	while (1)
	{
		input = readline("minishell> ");
		if (input == NULL)
		{
			printf("\n");
			exit(0);
		}
		if (ft_strlen(input) > 0)
			add_history(input);
		args = ft_split(input, ' ');
		free(input);
		if (args == NULL || args[0] == NULL)
		{
			ft_free_split(args);
			exit(0);
		}
		execute_command(args);
		ft_free_split(args);
	}
	return (0);
}
