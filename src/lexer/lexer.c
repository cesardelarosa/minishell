/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <code@cesardelarosa.xyz>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 17:20:26 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/04/03 22:45:48 by cesi             ###   ########.fr       */
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

	if (!input)
		return (NULL);
	tokens = NULL;
	s = input;
	while (*s)
	{
		while (*s && ft_iswhitespace(*s))
			s++;
		if (!*s || (*s == '\'' && process_single_quote(&s, &tokens) < 0)
			|| (*s == '\"' && process_double_quote(&s, &tokens) < 0))
			break ;
		if ((*s == '|' && process_pipe(&s, &tokens) == 0)
			|| (*s == '<' && process_redirect_in(&s, &tokens) == 0)
			|| (*s == '>' && process_redirect_out(&s, &tokens) == 0))
			continue ;
		process_word(&s, &tokens);
	}
	ft_lstadd_back(&tokens, ft_lstnew(create_token(TOKEN_EOF, NULL)));
	free(input);
	return (tokens);
}
