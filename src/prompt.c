/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <cde-la-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 17:56:41 by cde-la-r          #+#    #+#             */
/*   Updated: 2024/10/12 12:05:50 by cde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft.h"
#include "prompt.h"
#include "minishell.h"

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
void	print_prompt(void)
{
	char	*user;
	char	*host;
	char	*path;

	user = get_user();
	host = get_host();
	path = get_path();
	if (supports_colors())
		printf(BOLD_CYAN"%s"BOLD_WHITE" at "BOLD_YELLOW"%s"BOLD_WHITE
			" in "BOLD_GREEN"%s"BOLD_WHITE"\n$ "RESET, user, host, path);
	else
		printf("%s at %s in %s \n$ ", user, host, path);
	free(user);
	free(host);
	free(path);
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

	rl_replace_line("", 0);
	if (g_exit_status != 130)
		print_prompt();
	input = readline("");
	if (input == NULL)
		exit(EXIT_SUCCESS);
	if (ft_strlen(input) > 0)
		add_history(input);
	return (input);
}
