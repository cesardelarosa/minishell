/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_word.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <code@cesardelarosa.xyz>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 17:20:26 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/04/03 22:44:17 by cesi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "lexer_utils.h"
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>

static char	*read_word(const char **s)
{
	const char	*start;
	size_t		len;

	start = *s;
	while (**s && !ft_iswhitespace(**s) && **s != '|' && **s != '<'
		&& **s != '>' && **s != '$' && **s != '\'' && **s != '\"')
		(*s)++;
	len = *s - start;
	return (ft_substr(start, 0, len));
}

void	process_word(char **s, t_list **tokens)
{
	t_token	*token;
	char	*value;

	value = read_word((const char **)s);
	token = create_token(TOKEN_WORD, value);
	ft_lstadd_back(tokens, ft_lstnew(token));
}
