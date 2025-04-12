/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_word.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <code@cesardelarosa.xyz>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 17:20:26 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/04/08 12:14:57 by cde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "lexer_utils.h"
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>

static int	is_metachar(char c)
{
	if (c == '|' || c == '<' || c == '>' || c == '\'' || c == '\"' || c == '('
		|| c == ')')
		return (1);
	return (0);
}

static char	*read_word(const char **s)
{
	const char	*start;
	size_t		len;

	start = *s;
	while (**s && !ft_iswhitespace(**s) && !is_metachar(**s)
		&& !((*s)[0] == '&' && (*s)[1] == '&'))
		(*s)++;
	len = *s - start;
	return (ft_substr(start, 0, len));
}

void	process_word(char **s, t_list **tokens, int joined)
{
	t_token	*token;
	char	*value;

	value = read_word((const char **)s);
	token = create_token(TOKEN_WORD, value, joined);
	ft_lstadd_back(tokens, ft_lstnew(token));
}
