/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_parser_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <code@cesardelarosa.xyz>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 23:59:26 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/06/21 14:16:45 by cde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast_utils_bonus.h"
#include "core.h"
#include "libft.h"
#include <stdio.h>

#define SYNTAX_ERROR_MSG "syntax error near unexpected token"

static t_ast	*parse_expression(char **s, int *err);
void			skip_whitespace(char **s);
t_ast_type		peek_operator(char *s);
t_ast			*parse_pipeline_str(char **s, int *err);

static t_ast	*parse_group(char **s, int *err)
{
	t_ast	*node;

	(*s)++;
	node = parse_expression(s, err);
	if (*err)
		return (node);
	skip_whitespace(s);
	if (**s != ')')
	{
		ft_putstr_fd("minishell: " SYNTAX_ERROR_MSG " `)'\n", 2);
		*err = 1;
		ast_destroy(node);
		return (NULL);
	}
	(*s)++;
	return (node);
}

static t_ast	*parse_factor(char **s, int *err)
{
	skip_whitespace(s);
	if (**s == '(')
		return (parse_group(s, err));
	return (parse_pipeline_str(s, err));
}

static t_ast	*parse_term(char **s, int *err)
{
	t_ast	*node;
	t_ast	*right;

	node = parse_factor(s, err);
	if (*err || !node)
		return (node);
	while (peek_operator(*s) == AST_AND)
	{
		skip_whitespace(s);
		*s += 2;
		right = parse_factor(s, err);
		if (*err || !right)
		{
			if (!*err)
				ft_putstr_fd("minishell: " SYNTAX_ERROR_MSG " `&&'\n", 2);
			*err = 1;
			ast_destroy(node);
			return (NULL);
		}
		node = ast_create(AST_AND, node, right, NULL);
	}
	return (node);
}

static t_ast	*parse_expression(char **s, int *err)
{
	t_ast	*node;
	t_ast	*right;

	node = parse_term(s, err);
	if (*err || !node)
		return (node);
	while (peek_operator(*s) == AST_OR)
	{
		skip_whitespace(s);
		*s += 2;
		right = parse_term(s, err);
		if (*err || !right)
		{
			if (!*err)
				ft_putstr_fd("minishell: " SYNTAX_ERROR_MSG " `||'\n", 2);
			*err = 1;
			ast_destroy(node);
			return (NULL);
		}
		node = ast_create(AST_OR, node, right, NULL);
	}
	return (node);
}

t_ast	*ast_parser(char **s)
{
	int		error;
	t_ast	*root;

	error = 0;
	skip_whitespace(s);
	if (!**s)
		return (NULL);
	root = parse_expression(s, &error);
	skip_whitespace(s);
	if (**s != '\0' && !error)
	{
		ft_putstr_fd("minishell: " SYNTAX_ERROR_MSG "\n", 2);
		error = 1;
	}
	if (error && root)
	{
		ast_destroy(root);
		root = NULL;
	}
	return (root);
}
