/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <code@cesardelarosa.xyz>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 23:59:26 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/04/08 12:20:07 by cde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast_utils.h"
#include "lexer.h"
#include "libft.h"
#include "struct_creation.h"
#include "structs.h"
#include <stdlib.h>

t_command			*build_command(t_list **tokens_ptr, t_ctx *ctx);
static t_ast		*parse_expr(t_list **tokens, t_ctx *ctx, int *err);
static t_ast		*parse_factor(t_list **tokens, t_ctx *ctx, int *err);
static t_pipeline	*parse_pipeline(t_list **tokens, t_ctx *ctx, int *err);

t_ast	*ast_parser(t_list *tokens, t_ctx *ctx)
{
	int		err;
	t_ast	*root;
	t_token	*tok;

	err = 0;
	if (!tokens)
		return (NULL);
	root = parse_expr(&tokens, ctx, &err);
	if (!root)
		return (NULL);
	if (tokens)
	{
		tok = (t_token *)tokens->content;
		if (tok->type != TOKEN_EOF)
		{
			if (err == 0)
			{
				ft_putstr_fd("syntax error: unexpected token\n", 2);
				err = 1;
			}
			ast_destroy(root);
			return (NULL);
		}
	}
	return (root);
}

static t_ast	*parse_expr(t_list **tokens, t_ctx *ctx, int *err)
{
	t_ast	*left;
	t_ast	*node;
	t_token	*tok;
	t_ast	*right;

	left = parse_factor(tokens, ctx, err);
	if (!left)
		return (NULL);
	while (*tokens)
	{
		tok = (t_token *)(*tokens)->content;
		if (tok->type != TOKEN_AND && tok->type != TOKEN_OR)
			break ;
		*tokens = (*tokens)->next;
		right = parse_factor(tokens, ctx, err);
		if (!right)
		{
			if (*err == 0)
			{
				ft_putstr_fd("syntax error: invalid expression\n", 2);
				*err = 1;
			}
			ast_destroy(left);
			return (NULL);
		}
		if (tok->type == TOKEN_AND)
			node = ast_create(AST_AND, left, right, NULL);
		else
			node = ast_create(AST_OR, left, right, NULL);
		if (!node)
		{
			ast_destroy(left);
			ast_destroy(right);
			return (NULL);
		}
		left = node;
	}
	return (left);
}

static t_ast	*parse_factor(t_list **tokens, t_ctx *ctx, int *err)
{
	t_ast	*node;
	t_token	*tok;
	t_ast	*expr;

	if (!*tokens)
		return (NULL);
	tok = (t_token *)(*tokens)->content;
	if (tok->type == TOKEN_LPAREN)
	{
		*tokens = (*tokens)->next;
		expr = parse_expr(tokens, ctx, err);
		if (!expr)
		{
			if (*err == 0)
			{
				ft_putstr_fd("syntax error: invalid group expression\n", 2);
				*err = 1;
			}
			return (NULL);
		}
		if (!*tokens || ((t_token *)(*tokens)->content)->type != TOKEN_RPAREN)
		{
			if (*err == 0)
			{
				ft_putstr_fd("syntax error: missing ')'\n", 2);
				*err = 1;
			}
			ast_destroy(expr);
			return (NULL);
		}
		*tokens = (*tokens)->next;
		if (expr && expr->type == AST_PIPE && expr->pipeline
			&& expr->pipeline->cmd_count == 0)
		{
			if (*err == 0)
			{
				ft_putstr_fd("syntax error near unexpected token `)'\n", 2);
				*err = 1;
			}
			ast_destroy(expr);
			return (NULL);
		}
		node = ast_create(AST_GROUP, expr, NULL, NULL);
		if (!node)
		{
			ast_destroy(expr);
			return (NULL);
		}
		return (node);
	}
	else
	{
		node = malloc(sizeof(t_ast));
		if (!node)
			return (NULL);
		node->pipeline = parse_pipeline(tokens, ctx, err);
		if (!node->pipeline)
		{
			free(node);
			return (NULL);
		}
		if (node->pipeline->cmd_count == 0)
		{
			if (*err == 0)
			{
				ft_putstr_fd("syntax error: empty command\n", 2);
				*err = 1;
			}
			pipeline_destroy(node->pipeline);
			free(node);
			return (NULL);
		}
		node->type = AST_PIPE;
		node->left = NULL;
		node->right = NULL;
		return (node);
	}
}

static t_pipeline	*parse_pipeline(t_list **tokens, t_ctx *ctx, int *err)
{
	t_pipeline	*pipeline;
	t_command	*cmd;
	t_token		*tok;

	pipeline = pipeline_create(ctx);
	if (!pipeline || !*tokens)
		return (NULL);
	while (*tokens)
	{
		tok = (t_token *)(*tokens)->content;
		if (tok->type == TOKEN_EOF || tok->type == TOKEN_AND
			|| tok->type == TOKEN_OR || tok->type == TOKEN_RPAREN)
			break ;
		cmd = build_command(tokens, ctx);
		if (!cmd)
		{
			pipeline_destroy(pipeline);
			if (*err == 0)
			{
				ft_putstr_fd("syntax error: invalid command\n", 2);
				*err = 1;
			}
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
			tok = (t_token *)(*tokens)->content;
			if (tok->type == TOKEN_PIPE)
				*tokens = (*tokens)->next;
		}
	}
	return (pipeline);
}
