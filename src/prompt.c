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
#include <readline/readline.h>
#include <readline/history.h>
#include "libft.h"
#include "prompt.h"

int	colors_supported(void)
{
	char	*term;

	term = getenv("TERM");
	if (term == NULL)
		return (0);
	return (!ft_strncmp(term, "xterm", 6)
		|| !ft_strncmp(term, "xterm-color", 12)
		|| !ft_strncmp(term, "xterm-256color", 15)
		|| !ft_strncmp(term, "screen", 7)
		|| !ft_strncmp(term, "screen-256color", 16)
		|| !ft_strncmp(term, "tmux", 5)
		|| !ft_strncmp(term, "tmux-256color", 14));
}

static char	*build_colored_prompt(char *user, char *host, char *cwd)
{
	char	*prompt;

	prompt = ft_strjoin_free(ft_strdup(RED), user);
	prompt = ft_strjoin_free(prompt, RESET " at ");
	prompt = ft_strjoin_free(prompt, BLUE);
	prompt = ft_strjoin_free(prompt, host);
	prompt = ft_strjoin_free(prompt, RESET " in ");
	prompt = ft_strjoin_free(prompt, CYAN);
	prompt = ft_strjoin_free(prompt, cwd);
	prompt = ft_strjoin_free(prompt, RESET "\n$ ");
	free(host);
	return (prompt);
}

static char	*build_plain_prompt(char *user, char *host, char *cwd)
{
	char	*prompt;

	prompt = ft_strjoin_free(ft_strdup(user), " at ");
	prompt = ft_strjoin_free(prompt, host);
	prompt = ft_strjoin_free(prompt, " in ");
	prompt = ft_strjoin_free(prompt, cwd);
	prompt = ft_strjoin_free(prompt, "\n$ ");
	free(host);
	return (prompt);
}

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
	if (colors_supported())
		prompt = build_colored_prompt(get_user(), get_host(), cwd);
	else
		prompt = build_plain_prompt(get_user(), get_host(), cwd);
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
