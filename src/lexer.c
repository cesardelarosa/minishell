/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <cde-la-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 13:39:56 by cde-la-r          #+#    #+#             */
/*   Updated: 2024/10/01 17:46:43 by cde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

/*
** Checks if all quotes in the input string are properly closed.
** Counts the number of single and double quotes and returns true
** if both are even, indicating that they are closed.
**
** @param input: The string to check for closed quotes.
** @return: 1 if quotes are closed, 0 otherwise.
*/
int	are_quotes_closed(char *input)
{
	int	i;
	int	i_quotes;
	int	j_quotes;

	i = 0;
	i_quotes = 0;
	j_quotes = 0;
	while (input[i])
	{
		if (input[i] == '\'')
			i_quotes++;
		else if (input[i] == '\"')
			j_quotes++;
		i++;
	}
	return (i_quotes % 2 == 0 && j_quotes % 2 == 0);
}

/*
** The lexer function splits the input string into an array of tokens.
** It uses whitespace (' ') as the delimiter. After tokenization, the
** input string is freed since it's no longer needed.
**
** @param input: The input string to be tokenized.
** @return: A NULL-terminated array of strings (tokens).
*/
char	**lexer(char *input)
{
	char	**tokens;

	if (!input)
		return (NULL);
	tokens = ft_split(input, ' ');
	free(input);
	expand_all_vars(tokens);
	return (tokens);
}
