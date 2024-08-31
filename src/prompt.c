/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <cde-la-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 17:56:41 by cde-la-r          #+#    #+#             */
/*   Updated: 2024/08/30 17:56:41 by cde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft.h"
#include <readline/readline.h>
#include <readline/history.h>

char	*get_prompt(void)
{
	char	*prompt;
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
	{
		perror("minishell: getcwd()");
		exit(EXIT_FAILURE);
	}
	prompt = ft_strjoin(cwd, "$ ");
	if (prompt == NULL)
	{
		perror("minishell: ft_strjoin");
		exit(EXIT_FAILURE);
	}
	free(cwd);
	return (prompt);
}

char	*read_input(void)
{
	char	*input;
	char	*prompt;

	prompt = get_prompt();
	input = readline(prompt);
	free(prompt);
	if (input == NULL)
		exit(EXIT_SUCCESS);
	if (ft_strlen(input) > 0)
		add_history(input);
	return (input);
}
