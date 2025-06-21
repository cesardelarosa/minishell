/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_parser_utils_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <code@cesardelarosa.xyz>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 23:59:26 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/06/21 14:16:50 by cde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast_utils_bonus.h"
#include "core.h"
#include "libft.h"
#include <stdio.h>

#define SYNTAX_ERROR_MSG "syntax error near unexpected token"

void	skip_whitespace(char **s)
{
	while (ft_iswhitespace(**s))
		(*s)++;
}

t_ast_type	peek_operator(char *s)
{
	skip_whitespace(&s);
	if (ft_strncmp(s, "&&", 2) == 0)
		return (AST_AND);
	if (ft_strncmp(s, "||", 2) == 0)
		return (AST_OR);
	return (AST_ERROR);
}

static char	*extract_pipeline_str(char **s)
{
	char	*start;
	char	quote;

	start = *s;
	while (**s)
	{
		if (peek_operator(*s) != AST_ERROR || **s == '(' || **s == ')')
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

t_ast	*parse_pipeline_str(char **s, int *err)
{
	char	*pipeline_str;

	if (peek_operator(*s) != AST_ERROR || **s == ')')
	{
		ft_putstr_fd("minishell: " SYNTAX_ERROR_MSG "\n", 2);
		*err = 1;
		return (NULL);
	}
	pipeline_str = ft_strtrim(extract_pipeline_str(s), " \t");
	if (!pipeline_str || !*pipeline_str)
	{
		free(pipeline_str);
		if (**s)
		{
			ft_putstr_fd("minishell: " SYNTAX_ERROR_MSG "\n", 2);
			*err = 1;
		}
		return (NULL);
	}
	return (ast_create(AST_PIPE, NULL, NULL, pipeline_str));
}
