/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <code@cesardelarosa.xyz>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 18:08:20 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/04/07 17:33:33 by cesi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"
#include "struct_creation.h"
#include <stdio.h>
#include <stdlib.h>
#include "parse_token.h"

int	parse_token(t_command *cmd, t_list **tokens_ptr, t_list **arg_lst,
		t_ctx *ctx)
{
	t_token	*token;
	int		result;

	token = (t_token *)(*tokens_ptr)->content;
	if (token->type == TOKEN_ERROR)
		return (parse_error(token));
	if (token->type == TOKEN_REDIRECT_IN
		|| token->type == TOKEN_REDIRECT_OUT
		|| token->type == TOKEN_HEREDOC
		|| token->type == TOKEN_APPEND)
		return (parse_redirection(cmd, tokens_ptr, token->type, ctx));
	if (token->type == TOKEN_WORD
		|| token->type == TOKEN_SINGLE_QUOTED_STRING
		|| token->type == TOKEN_DOUBLE_QUOTED_STRING)
	{
		result = parse_word(arg_lst, token, ctx);
		*tokens_ptr = (*tokens_ptr)->next;
		return (result);
	}
	*tokens_ptr = (*tokens_ptr)->next;
	return (1);
}
