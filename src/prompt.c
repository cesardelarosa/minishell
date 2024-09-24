/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <cde-la-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 17:56:41 by cde-la-r          #+#    #+#             */
/*   Updated: 2024/09/19 14:58:14 by cde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft.h"
#include "prompt.h"

static char	*build_colored_prompt(void)
{
	char	*prompt;

	prompt = ft_strjoin_free(ft_strdup(BOLD_CYAN), get_user());
	prompt = ft_strjoin_free(prompt, BOLD_WHITE " at ");
	prompt = ft_strjoin_free(prompt, BOLD_YELLOW);
	prompt = ft_strjoin_free(prompt, get_host());
	prompt = ft_strjoin_free(prompt, BOLD_WHITE " in ");
	prompt = ft_strjoin_free(prompt, BOLD_GREEN);
	prompt = ft_strjoin_free(prompt, get_path());
	prompt = ft_strjoin_free(prompt, BOLD_WHITE " $ ");
	prompt = ft_strjoin_free(prompt, RESET);
	return (prompt);
}

static char	*build_plain_prompt(void)
{
	char	*prompt;

	prompt = ft_strjoin_free(ft_strdup(get_user()), " at ");
	prompt = ft_strjoin_free(prompt, get_host());
	prompt = ft_strjoin_free(prompt, " in ");
	prompt = ft_strjoin_free(prompt, get_path());
	prompt = ft_strjoin_free(prompt, " $ ");
	return (prompt);
}

char	*get_prompt(void)
{
	char	*prompt;
	char	*color;

	color = getenv("COLORTERM");
	if (color && ft_strncmp(color, "truecolor", 10) == 0)
		prompt = build_colored_prompt();
	else
		prompt = build_plain_prompt();
	if (prompt == NULL)
	{
		perror("minishell: ft_strjoin");
		exit(EXIT_FAILURE);
	}
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
