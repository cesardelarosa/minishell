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
		return (process_single_quote(s, tokens, joined));
	if (**s == '\"')
		return (process_double_quote(s, tokens, joined));
	if (**s == '|' )
		return (process_pipe(s, tokens));
	if (**s == '<')
		return (process_redirect_in(s, tokens));
	if (**s == '>' )
		return (process_redirect_out(s, tokens));
	return (process_word(s, tokens, joined));
}
