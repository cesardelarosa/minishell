/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_parser_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <code@cesardelarosa.xyz>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 23:59:26 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/06/20 13:31:01 by cde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast_utils_bonus.h"
#include "core.h"
#include "libft.h"
#include <stdio.h>

static t_ast		*parse_expression(char **s, int *err);

static void	skip_whitespace(char **s)
{
	while (ft_iswhitespace(**s))
		(*s)++;
}

static t_ast_type	peek_operator(char *s)
{
	skip_whitespace(&s);
	if (ft_strncmp(s, "&&", 2) == 0)
		return (AST_AND);
	if (ft_strncmp(s, "||", 2) == 0)
		return (AST_OR);
	if (*s == '(')
		return (AST_GROUP);
	return (AST_ERROR);
}

static char	*extract_pipeline(char **s)
{
	char	*start;
	char	quote;

	start = *s;
	while (**s)
	{
		if (peek_operator(*s) != AST_ERROR || **s == ')')
			break ;
		if (**s == '\'' || **s == '\"')
		{
			quote = **s;
			(*s)++;
			while (**s && **s != quote)
				(*s)++;
			if (**s)
				(*s)++;
		}
		else
			(*s)++;
	}
	return (ft_substr(start, 0, *s - start));
}

static t_ast	*parse_factor(char **s, int *err)
{
	t_ast	*node;
	char	*pipeline_str;

	skip_whitespace(s);
	if (**s == '(')
	{
		(*s)++;
		node = parse_expression(s, err);
		if (*err)
			return (node);
		skip_whitespace(s);
		if (**s != ')')
		{
			ft_putstr_fd("minishell: syntax error near unexpected token `)'\n",
				2);
			*err = 1;
			ast_destroy(node);
			return (NULL);
		}
		(*s)++;
		return (node);
	}
	if (peek_operator(*s) != AST_ERROR || **s == ')')
	{
		ft_putstr_fd("minishell: syntax error near unexpected token\n", 2);
		*err = 1;
		return (NULL);
	}
	pipeline_str = ft_strtrim(extract_pipeline(s), " \t");
	if (!pipeline_str || !*pipeline_str)
	{
		free(pipeline_str);
		if (**s)
		{
			ft_putstr_fd("minishell: syntax error near unexpected token\n", 2);
			*err = 1;
		}
		return (NULL);
	}
	return (ast_create(AST_PIPE, NULL, NULL, pipeline_str));
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
				ft_putstr_fd("minishell: syntax error near unexpected token `&&'\n",
					2);
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
				ft_putstr_fd("minishell: syntax error near unexpected token `||'\n",
					2);
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
		ft_putstr_fd("minishell: syntax error near unexpected token\n", 2);
		error = 1;
	}
	if (error && root)
	{
		ast_destroy(root);
		root = NULL;
	}
	return (root);
}
