/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <code@cesardelarosa.xyz>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 17:20:26 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/04/12 11:22:06 by cesi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "lexer_utils.h"
#include "lexer_utils_bonus.h"
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>

int	process_token(char **s, t_list **tokens, int joined)
{
	if (**s == '\'')
	{
		if (process_single_quote(s, tokens, joined) < 0)
			return (-1);
		return (1);
	}
	if (**s == '\"')
	{
		if (process_double_quote(s, tokens, joined) < 0)
			return (-1);
		return (1);
	}
	if (**s == '&' && (*s)[1] == '&' && process_and(s, tokens) == 0)
		return (1);
	if (**s == '|' && (*s)[1] == '|' && process_or(s, tokens) == 0)
		return (1);
	if (**s == '|' && process_pipe(s, tokens) == 0)
		return (1);
	if (**s == '<' && process_redirect_in(s, tokens) == 0)
		return (1);
	if (**s == '>' && process_redirect_out(s, tokens) == 0)
		return (1);
	if (**s == ')' && process_rparen(s, tokens) == 0)
		return (1);
	if (**s == '(' && process_lparen(s, tokens) == 0)
		return (1);
	process_word(s, tokens, joined);
	return (1);
}
