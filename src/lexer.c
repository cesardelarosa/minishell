/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrian <adrian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 13:39:56 by cde-la-r          #+#    #+#             */
/*   Updated: 2024/10/04 17:12:57 by adrian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <stdio.h>

/*
** Checks if a character is a quote.
**
** @param c: The character to check.
** @return: 1 if it's a quote, 0 otherwise.
*/
int	is_quotes(char c)
{
	return (c == '\'' || c == '\"');
}

/*
** Checks if all quotes in the input string are properly closed.
** Returns 1 if all are closed, otherwise returns 0.
**
** @param str: The string to check for closed quotes.
** @return: 1 if quotes are closed, 0 otherwise.
*/
int	are_quotes_closed(const char *str)
{
	int		i;
	char	quote_char;

	i = 0;
	if (str == NULL)
	{
		fprintf(stderr, "Error: Null string\n");
		return (0);
	}
	while (str[i])
	{
		if (is_quotes(str[i]))
		{
			quote_char = str[i];
			i++;
			while (str[i] && str[i] != quote_char)
				i++;
			if (str[i] == '\0')
				return (0);
		}
		i++;
	}
	return (1);
}

/*
** The lexer function splits the input string into an array of tokens.
** It uses whitespace (' ') as the delimiter. After tokenization,
** the input string is freed since it's no longer needed.
**
** @param input: The input string to be tokenized.
** @return: A NULL-terminated array of strings (tokens).
*/
char	**lexer(char *input)
{
	char	**tokens;

	if (!input)
		return (NULL);
	if (!are_quotes_closed(input))
	{
		perror("minishell: syntax error: unclosed quotes");
		free(input);
		g_exit_status = 1;
		return (NULL);
	}
	tokens = ft_split(input, ' ');
	free(input);
	if (!tokens)
		return (NULL);
//	expand_all_vars(tokens);
	return (tokens);
}
