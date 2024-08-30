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
#include "libft.h"
#include <readline/readline.h>
#include <readline/history.h>
#include "minishell.h"

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
			perror("minishell");
		waitpid(pid, &status, 0);
	}
	ft_free_split(args);
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

int	main(void)
{
	setup_signal_handlers();
	while (1)
		handle_command(parse_command(read_input()));
	return (0);
}
