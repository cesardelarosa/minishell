/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <code@cesardelarosa.xyz>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 23:59:26 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/04/07 23:59:34 by cde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"
#include "struct_creation.h"
#include "structs.h"
#include <stdlib.h>

t_command			*build_command(t_list **tokens_ptr, t_ctx *ctx);
static t_ast		*parse_expr(t_list **tokens, t_ctx *ctx);
static t_ast		*parse_factor(t_list **tokens, t_ctx *ctx);
static t_pipeline	*parse_pipeline(t_list **tokens, t_ctx *ctx);

t_ast	*ast_parser(t_list *tokens, t_ctx *ctx)
{
	t_ast	*root;

	if (!tokens)
		return (NULL);
	root = parse_expr(&tokens, ctx);
	return (root);
}

static t_ast	*parse_expr(t_list **tokens, t_ctx *ctx)
{
	t_ast	*left;
	t_ast	*node;
	t_token	*tok;

	left = parse_factor(tokens, ctx);
	if (!left)
		return (NULL);
	while (*tokens)
	{
		tok = (*tokens)->content;
		if (tok->type != TOKEN_AND && tok->type != TOKEN_OR)
			break ;
		*tokens = (*tokens)->next;
		node = (t_ast *)malloc(sizeof(t_ast));
		if (!node)
			return (NULL);
		node->left = left;
		node->right = parse_factor(tokens, ctx);
		if (!node->right)
		{
			free(node);
			return (NULL);
		}
		node->pipeline = NULL;
		if (tok->type == TOKEN_AND)
			node->type = AST_AND;
		else if (tok->type == TOKEN_OR)
			node->type = AST_OR;
		left = node;
	}
	return (left);
}

static t_ast	*parse_factor(t_list **tokens, t_ctx *ctx)
{
	t_ast	*node;
	t_token	*tok;
	t_ast	*expr;

	if (!*tokens)
		return (NULL);
	tok = (*tokens)->content;
	if (tok->type == TOKEN_LPAREN)
	{
		*tokens = (*tokens)->next;
		expr = parse_expr(tokens, ctx);
		if (!*tokens || ((t_token *)(*tokens)->content)->type != TOKEN_RPAREN)
			return (NULL);
		*tokens = (*tokens)->next;
		node = (t_ast *)malloc(sizeof(t_ast));
		if (!node)
			return (NULL);
		node->type = AST_GROUP;
		node->pipeline = NULL;
		node->left = expr;
		node->right = NULL;
		return (node);
	}
	else
	{
		node = (t_ast *)malloc(sizeof(t_ast));
		if (!node)
			return (NULL);
		node->pipeline = parse_pipeline(tokens, ctx);
		if (!node->pipeline)
		{
			free(node);
			return (NULL);
		}
		node->type = AST_PIPE;
		node->left = NULL;
		node->right = NULL;
		return (node);
	}
}

static t_pipeline	*parse_pipeline(t_list **tokens, t_ctx *ctx)
{
	t_pipeline	*pipeline;
	t_command	*cmd;
	t_token		*tok;

	pipeline = pipeline_create(ctx);
	if (!pipeline || !*tokens)
		return (NULL);
	while (*tokens)
	{
		tok = (*tokens)->content;
		if (tok->type == TOKEN_EOF || tok->type == TOKEN_AND
			|| tok->type == TOKEN_OR || tok->type == TOKEN_RPAREN)
			break ;
		cmd = build_command(tokens, ctx);
		if (!cmd)
		{
			pipeline_destroy(pipeline);
			return (NULL);
		}
		if (!pipeline_add_command(pipeline, cmd))
		{
			ft_putstr_fd("Error: failed to add command to pipeline\n", 2);
			pipeline_destroy(pipeline);
			return (NULL);
		}
		if (*tokens)
		{
			tok = (*tokens)->content;
			if (tok->type == TOKEN_PIPE)
				*tokens = (*tokens)->next;
		}
	}
	return (pipeline);
}
