/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <code@cesardelarosa.xyz>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 23:59:26 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/06/21 23:55:47 by cde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast_utils_bonus.h"
#include "lexer.h"
#include "expander.h"
#include "ft_glob_bonus.h"
#include "libft.h"
#include "parse_token.h"
#include "struct_creation.h"
#include "structs.h"
#include <stdlib.h>

int			handle_joined_token(t_list *arg_lst, char *expanded,
				t_token_type type, int is_multiple);
int			handle_normal_token(t_list **arg_lst, char *expanded,
				t_token_type type, int is_multiple);

static int	handle_globbing_token(t_list **arg_lst, t_token *token,
		char *expanded)
{
	t_list	*last_node;
	char	*full_pattern;
	t_list	*curr;

	if (token->joined && *arg_lst)
	{
		last_node = ft_lstlast(*arg_lst);
		full_pattern = ft_strjoin(last_node->content, expanded);
		free(expanded);
		if (!full_pattern)
			return (0);
		curr = *arg_lst;
		if (curr == last_node)
			*arg_lst = NULL;
		else
		{
			while (curr->next != last_node)
				curr = curr->next;
			curr->next = NULL;
		}
		ft_lstdelone(last_node, free);
		return (handle_globbing(arg_lst, full_pattern));
	}
	return (handle_globbing(arg_lst, expanded));
}

static int	parse_word_bonus(t_list **arg_lst, t_token *token, t_ctx *ctx)
{
	char	*expanded;
	int		is_multiple;

	expanded = expand_value(token->value, token->type, ctx, &is_multiple);
	if (!expanded)
		return (0);
	if (token->type == TOKEN_WORD && ft_strchr(expanded, '*'))
		return (handle_globbing_token(arg_lst, token, expanded));
	if (token->joined && *arg_lst)
		return (handle_joined_token(*arg_lst, expanded, token->type,
				is_multiple));
	return (handle_normal_token(arg_lst, expanded, token->type, is_multiple));
}

int	parse_token(t_command *cmd, t_list **tokens_ptr, t_list **arg_lst,
		t_ctx *ctx)
{
	t_token	*token;
	int		result;

	token = (t_token *)(*tokens_ptr)->content;
	if (token->type == TOKEN_ERROR)
		return (parse_error(token));
	if (token->type == TOKEN_REDIRECT_IN || token->type == TOKEN_REDIRECT_OUT
		|| token->type == TOKEN_HEREDOC || token->type == TOKEN_APPEND)
		return (parse_redirection(cmd, tokens_ptr, token->type, ctx));
	if (token->type == TOKEN_WORD || token->type == TOKEN_SINGLE_QUOTED_STRING
		|| token->type == TOKEN_DOUBLE_QUOTED_STRING)
	{
		result = parse_word_bonus(arg_lst, token, ctx);
		*tokens_ptr = (*tokens_ptr)->next;
		return (result);
	}
	*tokens_ptr = (*tokens_ptr)->next;
	return (1);
}
