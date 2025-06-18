/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <code@cesardelarosa.xyz>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 23:59:26 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/06/18 11:08:44 by cesi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "ast_utils_bonus.h"
#include "expander.h"
#include "ft_glob_bonus.h"
#include "libft.h"
#include "parse_token.h"
#include "struct_creation.h"
#include "structs.h"
#include <stdlib.h>

int					parse_token_bonus(t_command *cmd, t_list **tokens_ptr,
						t_list **arg_lst, t_ctx *ctx);
t_command			*build_command(t_list **tokens_ptr, t_ctx *ctx,
						t_token_parser_ft parse_ft);
static t_ast		*parse_expr(t_list **tokens, t_ctx *ctx, int *err);

static t_pipeline	*parse_pipeline(t_list **tokens, t_ctx *ctx, int *err)
{
	t_pipeline	*pipeline;
	t_command	*cmd;
	t_token		*tok;

	pipeline = pipeline_create(ctx);
	while (*tokens)
	{
		tok = (t_token *)(*tokens)->content;
		if (tok->type == TOKEN_EOF || tok->type == TOKEN_AND
			|| tok->type == TOKEN_OR || tok->type == TOKEN_RPAREN)
			break ;
		cmd = build_command(tokens, ctx, &parse_token_bonus);
		if (!cmd)
		{
			*err = 1;
			pipeline_destroy(pipeline);
			return (NULL);
		}
		pipeline_add_command(pipeline, cmd);
		if (*tokens && ((t_token *)(*tokens)->content)->type == TOKEN_PIPE)
			*tokens = (*tokens)->next;
		else
			break ;
	}
	return (pipeline);
}

static t_ast	*parse_factor(t_list **tokens, t_ctx *ctx, int *err)
{
	t_ast	*node;
	t_token	*tok;

	tok = (t_token *)(*tokens)->content;
	if (tok->type == TOKEN_LPAREN)
	{
		*tokens = (*tokens)->next;
		node = parse_expr(tokens, ctx, err);
		if (!node || *err)
			return (node);
		if (!*tokens || ((t_token *)(*tokens)->content)->type != TOKEN_RPAREN)
		{
			*err = 1;
			ft_putstr_fd("minishell: syntax error: missing ')'\n", 2);
			return (ast_destroy(node), NULL);
		}
		*tokens = (*tokens)->next;
		return (ast_create(AST_GROUP, node, NULL, NULL));
	}
	node = ast_create(AST_PIPE, NULL, NULL, NULL);
	node->pipeline = parse_pipeline(tokens, ctx, err);
	if (!node->pipeline || *err)
		return (ast_destroy(node), NULL);
	return (node);
}

static t_ast_type	token_to_ast_type(t_token_type token_type)
{
	if (token_type == TOKEN_AND)
		return (AST_AND);
	if (token_type == TOKEN_OR)
		return (AST_OR);
	return (AST_ERROR);
}

static t_ast	*parse_expr(t_list **tokens, t_ctx *ctx, int *err)
{
	t_ast	*left;
	t_ast	*node;
	t_token	*tok;
	t_ast	*right;

	left = parse_factor(tokens, ctx, err);
	if (!left || *err)
		return (left);
	while (*tokens)
	{
		tok = (t_token *)(*tokens)->content;
		if (tok->type != TOKEN_AND && tok->type != TOKEN_OR)
			break ;
		*tokens = (*tokens)->next;
		right = parse_factor(tokens, ctx, err);
		if (!right)
		{
			*err = 1;
			ast_destroy(left);
			return (NULL);
		}
		node = ast_create(token_to_ast_type(tok->type), left, right, NULL);
		left = node;
	}
	return (left);
}

t_ast	*ast_parser(t_list *tokens, t_ctx *ctx)
{
	int		err;
	t_ast	*root;

	err = 0;
	if (!tokens)
		return (NULL);
	root = parse_expr(&tokens, ctx, &err);
	if (err)
	{
		if (root)
			ast_destroy(root);
		return (NULL);
	}
	if (tokens && ((t_token *)tokens->content)->type != TOKEN_EOF)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token\n", 2);
		ast_destroy(root);
		return (NULL);
	}
	return (root);
}
