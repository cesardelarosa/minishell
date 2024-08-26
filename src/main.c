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
#include "libft.h"

void	handle_command(char *input)
{
	printf("Error: comando no reconocido -> %s\n", input);
}

int	main(void)
{
	char	*input;
	int		running;

	running = 1;
	while (running)
	{
		input = readline("minishell> ");
		if (input == NULL)
		{
			printf("\n");
			exit(0);
		}
		if (ft_strlen(input) > 0)
			add_history(input);
		if (ft_strncmp(input, "exit", 5) == 0)
			running = 0;
		else
			handle_command(input);
		free(input);
	}
	return (0);
}
