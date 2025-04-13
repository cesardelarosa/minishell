/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <code@cesardelarosa.xyz>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 17:20:26 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/04/13 12:44:39 by cesi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "lexer_utils.h"
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
	if (**s == '|' && process_pipe(s, tokens) == 0)
		return (1);
	if (**s == '<' && process_redirect_in(s, tokens) == 0)
		return (1);
	if (**s == '>' && process_redirect_out(s, tokens) == 0)
		return (1);
	process_word(s, tokens, joined);
	return (1);
}
