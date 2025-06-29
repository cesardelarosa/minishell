/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_single_quote.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <code@cesardelarosa.xyz>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 17:20:26 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/04/04 16:41:58 by cesi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>

static char	*read_single_quoted(const char **s)
{
	const char	*start;
	char		*str;
	size_t		len;

	(*s)++;
	start = *s;
	while (**s && **s != '\'')
		(*s)++;
	if (**s != '\'')
		return (NULL);
	len = *s - start;
	str = ft_substr(start, 0, len);
	(*s)++;
	return (str);
}

int	process_single_quote(char **s, t_list **tokens, int joined)
{
	t_token	*token;
	char	*value;

	value = read_single_quoted((const char **)s);
	if (!value)
	{
		ft_putstr_fd("minishell: syntax error: unclosed single quote\n", 2);
		return (-1);
	}
	token = create_token(TOKEN_SINGLE_QUOTED_STRING, value, joined);
	ft_lstadd_back(tokens, ft_lstnew(token));
	return (0);
}
