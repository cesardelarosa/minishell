/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <code@cesardelarosa.xyz>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 18:08:20 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/06/23 15:20:33 by cde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"
#include "struct_creation.h"
#include <stdio.h>
#include <stdlib.h>
#include "signals.h"

extern volatile sig_atomic_t	g_sigint_received;

int			parse_token(t_command *cmd, t_list **tokens_ptr, t_list **arg_lst,
				t_ctx *ctx);
t_command	*parse_command(t_list **tokens_ptr, t_ctx *ctx,
				t_token_parser_ft parse_ft);

static t_pipeline	*parsing_error(t_pipeline *p, t_token *token)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	if (token && token->value)
		ft_putstr_fd(token->value, 2);
	else
		ft_putstr_fd("newline", 2);
	ft_putstr_fd("'\n", 2);
	if (p)
		pipeline_destroy(p);
	return (NULL);
}

static int	handle_post_command_token(t_list **current_tokens, t_pipeline *p)
{
	t_token	*token_data;
	t_token	*next_token;

	token_data = (t_token *)(*current_tokens)->content;
	if (token_data->type == TOKEN_EOF)
		return (1);
	if (token_data->type == TOKEN_PIPE)
	{
		next_token = (t_token *)(*current_tokens)->next->content;
		if (next_token->type == TOKEN_EOF || next_token->type == TOKEN_PIPE)
		{
			parsing_error(p, next_token);
			return (0);
		}
		*current_tokens = (*current_tokens)->next;
		return (1);
	}
	parsing_error(p, token_data);
	return (0);
}

t_pipeline	*parser(t_list *tokens, t_ctx *ctx)
{
	t_pipeline	*p;
	t_command	*cmd;
	t_list		*current_tokens;

	p = pipeline_create(ctx);
	if (!p)
		return (NULL);
	current_tokens = tokens;
	while (((t_token *)current_tokens->content)->type != TOKEN_EOF)
	{
		cmd = parse_command(&current_tokens, ctx, &parse_token);
		if (!cmd)
		{
			if (g_sigint_received)
			{
				pipeline_destroy(p);
				return (NULL);
			}
			return (parsing_error(p, (t_token *)current_tokens->content));
		}
		if (!pipeline_add_command(p, cmd))
			return (parsing_error(p, NULL));
		if (!handle_post_command_token(&current_tokens, p))
			return (NULL);
	}
	return (p);
}
