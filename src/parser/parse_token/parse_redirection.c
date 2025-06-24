/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <code@cesardelarosa.xyz>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 21:25:45 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/06/25 00:38:48 by cde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "lexer.h"
#include "libft.h"
#include "struct_creation.h"
#include "signals.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

extern volatile sig_atomic_t	g_sigint_received;

char	*expand_value(char *value, t_token_type type, t_ctx *ctx,
			int *is_multiple);

static int	check_token_existence(t_list **tokens_ptr)
{
	if (!(*tokens_ptr)->next
		|| ((t_token *)(*tokens_ptr)->next->content)->type == TOKEN_EOF)
		return (0);
	*tokens_ptr = (*tokens_ptr)->next;
	return (1);
}

static int	validate_token_type(t_token *token)
{
	return (token->type == TOKEN_WORD
		|| token->type == TOKEN_SINGLE_QUOTED_STRING
		|| token->type == TOKEN_DOUBLE_QUOTED_STRING);
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

static int	handle_heredoc(t_command *cmd, t_token *token, t_ctx *ctx)
{
	bool	expand;
	char	*delimiter;
	char	*buffer;
	t_redir	*redir;
	t_list	*node;

	expand = (token->type == TOKEN_WORD);
	delimiter = ft_strdup(token->value);
	if (!delimiter)
		return (0);
	setup_signals(HEREDOC_MODE);
	buffer = read_heredoc_input(delimiter, expand, ctx);
	setup_signals(INTERACTIVE_MODE);
	if (!buffer)
		return (free(delimiter), -1);
	redir = redir_create(TOKEN_HEREDOC, delimiter, cmd);
	free(delimiter);
	if (!redir)
		return (free(buffer), 0);
	redir->heredoc_buf = buffer;
	node = ft_lstnew(redir);
	if (!node)
		return (redir_destroy(redir), 0);
	ft_lstadd_back(&cmd->redirs, node);
	return (1);
}

int	parse_redirection(t_command *cmd, t_list **tokens_ptr,
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
	if (op_type == TOKEN_HEREDOC)
		ret = handle_heredoc(cmd, token, ctx);
	else
	{
		ret = process_expansion(token, ctx, &expanded);
		if (ret == 0)
			return (0);
		if (ret == 1)
		{
			command_add_redir(cmd, op_type, expanded);
			free(expanded);
		}
	}
	if (ret == 1 || ret == 2)
		*tokens_ptr = (*tokens_ptr)->next;
	return (ret == 1);
}
