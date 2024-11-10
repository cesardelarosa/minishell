/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrian <adrian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 13:39:56 by cde-la-r          #+#    #+#             */
/*   Updated: 2024/11/07 09:23:29 by adrian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <stdio.h>

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
		if (ft_isquote(str[i]))
		{
			quote_char = str[i];
			i++;
			while (str[i] && str[i] != quote_char)
				i++;
			if (str[i] == '\0')
				return (0);
			i++;
		}
		else
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

int	calc_len_new_str(char *str)
{
	char	quote_char;
	int		i;
	int		len;

	i = 0;
	len = 0;
	while (str[i])
	{
		if (ft_isquote(str[i]))
		{
			quote_char = str[i];
			i++;
			while (str[i] && str[i] != quote_char)
			{
				len++;
				i++;
			}
		}
		else
			len++;
		i++;
	}
	return (len);
}

int	handle_unclosed_quotes(char **str, char *new_str)
{
	free(new_str);
	free(*str);
	*str = NULL;
	g_exit_status = 1;
	return (1);
}

char	**lexer(char *input)
{
	char	**tokens;
	int		i;

	i = 0;
	if (!input)
		return (NULL);
	if (!are_quotes_closed(input))
	{
		perror("minishell: syntax error: unclosed quotes");
		g_exit_status = 1;
		return (NULL);
	}
	tokens = parser_comand(input, &i);
	expand_all_vars(tokens);
	i = 0;
	while (tokens && tokens[i])
		sup_quotes(&(tokens[i++]), 0, 0);
	free(input);
	if (!tokens)
		return (NULL);
	return (tokens);
}
