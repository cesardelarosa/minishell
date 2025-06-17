/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_parser_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <code@cesardelarosa.xyz>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 23:59:26 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/06/17 21:17:05 by cesi             ###   ########.fr       */
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

static t_ast		*parse_expr(t_list **tokens, t_ctx *ctx, int *err);
static t_ast		*parse_factor(t_list **tokens, t_ctx *ctx, int *err);
static t_pipeline	*parse_pipeline(t_list **tokens, t_ctx *ctx, int *err);
static t_command	*build_command(t_list **tokens_ptr, t_ctx *ctx);
static int			parse_token_bonus(t_command *cmd, t_list **tokens_ptr,
						t_list **arg_lst, t_ctx *ctx);
static int			parse_word_bonus(t_list **arg_lst, t_token *token,
						t_ctx *ctx);
int					handle_joined_token(t_list *arg_lst, char *expanded,
						t_token_type type, int is_multiple);
int					handle_normal_token(t_list **arg_lst, char *expanded,
						t_token_type type, int is_multiple);

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
		node = ast_create(tok->type, left, right, NULL);
		left = node;
	}
	return (left);
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
		cmd = build_command(tokens, ctx);
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

static t_command	*build_command(t_list **tokens_ptr, t_ctx *ctx)
{
	t_command	*cmd;
	t_list		*arg_list;
	t_token		*token;
	t_list		*current_arg;
	int			i;

	cmd = command_create(NULL);
	arg_list = NULL;
	while (*tokens_ptr)
	{
		token = (t_token *)(*tokens_ptr)->content;
		if (token->type == TOKEN_PIPE || token->type == TOKEN_EOF
			|| token->type == TOKEN_AND || token->type == TOKEN_OR
			|| token->type == TOKEN_RPAREN)
			break ;
		if (!parse_token_bonus(cmd, tokens_ptr, &arg_list, ctx))
		{
			command_destroy(cmd);
			ft_lstclear(&arg_list, free);
			return (NULL);
		}
	}
	cmd->argv = (char **)ft_calloc(ft_lstsize(arg_list) + 1, sizeof(char *));
	current_arg = arg_list;
	i = 0;
	while (current_arg)
	{
		cmd->argv[i] = ft_strdup((char *)current_arg->content);
		current_arg = current_arg->next;
		i++;
	}
	ft_lstclear(&arg_list, free);
	return (cmd);
}

static int	parse_token_bonus(t_command *cmd, t_list **tokens_ptr,
		t_list **arg_lst, t_ctx *ctx)
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

static int	parse_word_bonus(t_list **arg_lst, t_token *token, t_ctx *ctx)
{
	char	*expanded;
	int		is_multiple;
	t_list	*last_node;
	char	*full_pattern;
	t_list	*curr;

	expanded = expand_value(token->value, token->type, ctx, &is_multiple);
	if (!expanded)
		return (0);
	if (token->type == TOKEN_WORD && ft_strchr(expanded, '*'))
	{
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
	if (token->joined && *arg_lst)
		return (handle_joined_token(*arg_lst, expanded, token->type,
				is_multiple));
	return (handle_normal_token(arg_lst, expanded, token->type, is_multiple));
}
