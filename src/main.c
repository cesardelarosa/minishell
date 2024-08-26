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

void	execute_command(t_vars *vars)
{
	char	**args;
	pid_t	pid;
	int		status;

	args = ft_split(vars->input, ' ');
	if (args == NULL || args[0] == NULL)
	{
		ft_free_split(args);
		return ;
	}
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
	ft_free_split(args);
}

void	handle_command(t_vars *vars)
{
	if (ft_strlen(vars->input) > 0)
		add_history(vars->input);
	if (ft_strncmp(vars->input, "exit", 5) == 0)
		vars->running = 0;
	else
		execute_command(vars);
}

void	init_vars(t_vars *vars)
{
	vars->running = 1;
	vars->input = NULL;
}

void	shell_loop(t_vars *vars)
{
	while (vars->running)
	{
		vars->input = readline("minishell> ");
		if (vars->input == NULL)
		{
			printf("\n");
			exit(0);
		}
		handle_command(vars);
		free(vars->input);
	}
}

int	main(void)
{
	t_vars	vars;

	init_vars(&vars);
	shell_loop(&vars);
	return (0);
}
