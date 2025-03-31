/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <code@cesardelarosa.xyz>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 18:08:20 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/03/31 23:33:29 by cesi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "struct_creation.h"
#include <stdio.h>
#include <stdlib.h>
#include "lexer.h"

static int	handle_redirection(t_command *cmd, t_list **tokens_ptr,
	t_token_type op_type)
{
	t_token	*token;

	*tokens_ptr = (*tokens_ptr)->next;
	if (!*tokens_ptr)
	{
		ft_putstr_fd("Error: redirection operator without target\n", 2);
		return (0);
	}
	token = (t_token *)(*tokens_ptr)->content;
	if (token->type != TOKEN_WORD && token->type != TOKEN_VARIABLE
		&& token->type != TOKEN_SINGLE_QUOTED_STRING
		&& token->type != TOKEN_DOUBLE_QUOTED_STRING)
	{
		ft_putstr_fd("Error: redirection target must be a word\n", 2);
		return (0);
	}
	if (op_type == TOKEN_REDIRECT_IN)
		command_add_redir(cmd, REDIR_INPUT, token->value);
	else if (op_type == TOKEN_REDIRECT_OUT)
		command_add_redir(cmd, REDIR_OUTPUT, token->value);
	else if (op_type == TOKEN_HEREDOC)
		command_add_redir(cmd, REDIR_HEREDOC, token->value);
	else if (op_type == TOKEN_APPEND)
		command_add_redir(cmd, REDIR_APPEND, token->value);
	return (1);
}

static int	handle_argument(t_list **arg_list, t_token *token)
{
	char	*dup;

	dup = ft_strdup(token->value);
	if (!dup)
		return (0);
	ft_lstadd_back(arg_list, ft_lstnew(dup));
	return (1);
}

static int	handle_error_token(t_token *token)
{
	ft_putstr_fd("Error: ", 2);
	ft_putstr_fd(token->value, 2);
	ft_putstr_fd("\n", 2);
	return (0);
}

int	process_token(t_command *cmd, t_list **tokens_ptr, t_list **arg_lst)
{
	t_token	*token;

	token = (t_token *)(*tokens_ptr)->content;
	if (token->type == TOKEN_REDIRECT_IN || token->type == TOKEN_REDIRECT_OUT
		|| token->type == TOKEN_HEREDOC || token->type == TOKEN_APPEND)
	{
		if (!handle_redirection(cmd, tokens_ptr, token->type))
			return (0);
	}
	else if (token->type == TOKEN_WORD || token->type == TOKEN_VARIABLE
		|| token->type == TOKEN_SINGLE_QUOTED_STRING
		|| token->type == TOKEN_DOUBLE_QUOTED_STRING)
	{
		if (!handle_argument(arg_lst, token))
			return (0);
	}
	else if (token->type == TOKEN_ERROR)
		return (handle_error_token(token));
	*tokens_ptr = (*tokens_ptr)->next;
	return (1);
}
