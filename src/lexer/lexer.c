/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <code@cesardelarosa.xyz>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 17:20:26 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/04/04 17:22:36 by cesi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "lexer_utils.h"
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>

t_list	*lexer(char *input)
{
	t_list	*tokens;
	char	*s;
	char	*ws;
	int		joined;

	if (!input)
		return (NULL);
	tokens = NULL;
	s = input;
	while (*s)
	{
		ws = s;
		while (*ws && ft_iswhitespace(*ws))
			ws++;
		joined = (ws == s);
		s = ws;
		if (!*s || process_token(&s, &tokens, joined) < 0)
			break ;
	}
	ft_lstadd_back(&tokens, ft_lstnew(create_token(TOKEN_EOF, NULL, 0)));
	free(input);
	return (tokens);
}
