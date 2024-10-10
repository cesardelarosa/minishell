/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <cde-la-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 17:56:41 by cde-la-r          #+#    #+#             */
/*   Updated: 2024/09/26 15:28:40 by cde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft.h"
#include "prompt.h"
/*
** Builds a colored prompt string including user, host, and current path.
**
** @return: The constructed colored prompt string.
*/
static char	*build_colored_prompt(void)
{
	char	*prompt;

	prompt = ft_strjoin_free(ft_strdup(BOLD_CYAN), get_user());
	prompt = ft_strjoin_free(prompt, ft_strdup(BOLD_WHITE " at "));
	prompt = ft_strjoin_free(prompt, ft_strdup(BOLD_YELLOW));
	prompt = ft_strjoin_free(prompt, get_host());
	prompt = ft_strjoin_free(prompt, ft_strdup(BOLD_WHITE " in "));
	prompt = ft_strjoin_free(prompt, ft_strdup(BOLD_GREEN));
	prompt = ft_strjoin_free(prompt, get_path());
	prompt = ft_strjoin_free(prompt, ft_strdup(BOLD_WHITE " $ "));
	prompt = ft_strjoin_free(prompt, ft_strdup(RESET));
	return (prompt);
}

/*
** Builds a plain prompt string including user, host, and current path.
**
** @return: The constructed plain prompt string.
*/
static char	*build_plain_prompt(void)
{
	char	*prompt;

	prompt = ft_strjoin_free(get_user(), ft_strdup(" at "));
	prompt = ft_strjoin_free(prompt, ft_strdup(get_host()));
	prompt = ft_strjoin_free(prompt, ft_strdup(" in "));
	prompt = ft_strjoin_free(prompt, get_path());
	prompt = ft_strjoin_free(prompt, ft_strdup(" $ "));
	return (prompt);
}

/*
** Checks if the terminal supports colors based on the TERM and COLORTERM
** environment variables.
**
** @return: 1 if colors are supported, 0 otherwise.
*/
static int	supports_colors(void)
{
	char	*term;
	char	*colorterm;

	term = getenv("TERM");
	if (term && (ft_strnstr(term, "xterm", 5)
			|| ft_strnstr(term, "screen", 6)
			|| ft_strnstr(term, "color", 5)
			|| ft_strnstr(term, "linux", 5)
			|| ft_strnstr(term, "ansi", 4)))
		return (1);
	colorterm = getenv("COLORTERM");
	if (colorterm && (ft_strncmp(colorterm, "truecolor", 9) == 0
			|| ft_strncmp(colorterm, "24bit", 5) == 0))
		return (1);
	return (0);
}

/*
** Gets the prompt string based on terminal color support.
**
** @return: The constructed prompt string, either colored or plain.
*/
char	*get_prompt(void)
{
	char	*prompt;

	if (supports_colors())
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

/*
** Reads user input from the command line using readline, handling prompt 
** display and history.
**
** @return: The input string entered by the user.
*/
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
