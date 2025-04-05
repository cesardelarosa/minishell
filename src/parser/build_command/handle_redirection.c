/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <code@cesardelarosa.xyz>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 21:25:45 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/04/05 21:25:48 by cde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"
#include "struct_creation.h"
#include <stdlib.h>
#include <stdio.h>

char	*expand_value(char *value, t_token_type type, t_ctx *ctx,
			int *is_multiple);

static int	check_token_existence(t_list **tokens_ptr)
{
	*tokens_ptr = (*tokens_ptr)->next;
	if (!*tokens_ptr)
	{
		ft_putstr_fd("Error: redirection operator without target\n", 2);
		return (0);
	}
	return (1);
}

static int	validate_token_type(t_token *token)
{
	if (token->type != TOKEN_WORD
		&& token->type != TOKEN_SINGLE_QUOTED_STRING
		&& token->type != TOKEN_DOUBLE_QUOTED_STRING)
	{
		ft_putstr_fd("Error: redirection target must be a word\n", 2);
		return (0);
	}
	return (1);
}

static int	process_expansion(t_token *token, t_ctx *ctx, char **expanded)
{
	int	is_multiple;

	*expanded = expand_value(token->value, token->type, ctx, &is_multiple);
	if (!*expanded)
		return (0);
	if (is_multiple)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(token->value, 2);
		ft_putstr_fd(": ambiguous redirect\n", 2);
		free(*expanded);
		return (2);
	}
	return (1);
}

static void	add_redirection(t_command *cmd, t_token_type op_type,
		char *expanded)
{
	if (op_type == TOKEN_REDIRECT_IN)
		command_add_redir(cmd, REDIR_INPUT, expanded);
	else if (op_type == TOKEN_REDIRECT_OUT)
		command_add_redir(cmd, REDIR_OUTPUT, expanded);
	else if (op_type == TOKEN_HEREDOC)
		command_add_redir(cmd, REDIR_HEREDOC, expanded);
	else if (op_type == TOKEN_APPEND)
		command_add_redir(cmd, REDIR_APPEND, expanded);
}

int	handle_redirection(t_command *cmd, t_list **tokens_ptr,
		t_token_type op_type, t_ctx *ctx)
{
	t_token	*token;
	char	*expanded;
	int		ret;

	if (!check_token_existence(tokens_ptr))
		return (0);
	token = (t_token *)(*tokens_ptr)->content;
	if (!validate_token_type(token))
		return (0);
	ret = process_expansion(token, ctx, &expanded);
	if (ret == 0)
		return (0);
	else if (ret == 2)
	{
		*tokens_ptr = (*tokens_ptr)->next;
		return (0);
	}
	add_redirection(cmd, op_type, expanded);
	free(expanded);
	*tokens_ptr = (*tokens_ptr)->next;
	return (1);
}
