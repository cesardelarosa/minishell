/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <cde-la-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 13:39:56 by cde-la-r          #+#    #+#             */
/*   Updated: 2024/09/26 15:26:27 by cde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
	return (tokens);
}
