/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <code@cesardelarosa.xyz>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 17:20:26 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/03/31 19:53:26 by cesi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>

/*
static int	is_valid_var_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}

static char	*read_variable(const char **s)
{
	const char	*start;
	char		*var;
	size_t		len;

	(*s)++;
	if (**s == '?')
	{
		var = ft_strdup("?");
		(*s)++;
		return (var);
	}
	start = *s;
	while (**s && is_valid_var_char(**s))
		(*s)++;
	len = *s - start;
	return (ft_substr(start, 0, len));
}

static int	process_variable(char **s, t_list **tokens)
{
	t_token	*token;
	char	*value;

	value = read_variable((const char **)s);
	token = create_token(TOKEN_VARIABLE, value);
	ft_lstadd_back(tokens, ft_lstnew(token));
	return (0);
}
*/

static int	is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

static char	*read_single_quoted(const char **s)
{
	const char	*start;
	char		*str;
	size_t		len;

	(*s)++;
	start = *s;
	while (**s && **s != '\'')
		(*s)++;
	if (**s != '\'')
		return (NULL);
	len = *s - start;
	str = ft_substr(start, 0, len);
	(*s)++;
	return (str);
}

static char	*read_double_quoted(const char **s)
{
	const char	*start;
	char		*str;
	size_t		len;

	(*s)++;
	start = *s;
	while (**s && **s != '\"')
		(*s)++;
	if (**s != '\"')
		return (NULL);
	len = *s - start;
	str = ft_substr(start, 0, len);
	(*s)++;
	return (str);
}

static char	*read_word(const char **s)
{
	const char	*start;
	size_t		len;

	start = *s;
	while (**s && !is_whitespace(**s) && **s != '|' && **s != '<' && **s != '>'
		&& **s != '$' && **s != '\'' && **s != '\"')
		(*s)++;
	len = *s - start;
	return (ft_substr(start, 0, len));
}

t_token	*create_token(t_token_type type, char *value)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->value = value;
	return (token);
}

void	free_token(void *token_ptr)
{
	t_token	*token;

	token = (t_token *)token_ptr;
	if (token)
	{
		free(token->value);
		free(token);
	}
}

static int	process_pipe(char **s, t_list **tokens)
{
	t_token	*token;

	token = create_token(TOKEN_PIPE, ft_strdup("|"));
	ft_lstadd_back(tokens, ft_lstnew(token));
	(*s)++;
	return (0);
}

static int	process_redirect_in(char **s, t_list **tokens)
{
	t_token	*token;

	if ((*s)[1] == '<')
	{
		token = create_token(TOKEN_HEREDOC, ft_strdup("<<"));
		ft_lstadd_back(tokens, ft_lstnew(token));
		(*s) += 2;
	}
	else
	{
		token = create_token(TOKEN_REDIRECT_IN, ft_strdup("<"));
		ft_lstadd_back(tokens, ft_lstnew(token));
		(*s)++;
	}
	return (0);
}

static int	process_redirect_out(char **s, t_list **tokens)
{
	t_token	*token;

	if ((*s)[1] == '>')
	{
		token = create_token(TOKEN_APPEND, ft_strdup(">>"));
		ft_lstadd_back(tokens, ft_lstnew(token));
		(*s) += 2;
	}
	else
	{
		token = create_token(TOKEN_REDIRECT_OUT, ft_strdup(">"));
		ft_lstadd_back(tokens, ft_lstnew(token));
		(*s)++;
	}
	return (0);
}

static int	process_single_quote(char **s, t_list **tokens)
{
	t_token	*token;
	char	*value;

	value = read_single_quoted((const char **)s);
	if (!value)
	{
		token = create_token(TOKEN_ERROR, ft_strdup("Unclosed single quote"));
		ft_lstadd_back(tokens, ft_lstnew(token));
		return (-1);
	}
	token = create_token(TOKEN_SINGLE_QUOTED_STRING, value);
	ft_lstadd_back(tokens, ft_lstnew(token));
	return (0);
}

static int	process_double_quote(char **s, t_list **tokens)
{
	t_token	*token;
	char	*value;

	value = read_double_quoted((const char **)s);
	if (!value)
	{
		token = create_token(TOKEN_ERROR, ft_strdup("Unclosed double quote"));
		ft_lstadd_back(tokens, ft_lstnew(token));
		return (-1);
	}
	token = create_token(TOKEN_DOUBLE_QUOTED_STRING, value);
	ft_lstadd_back(tokens, ft_lstnew(token));
	return (0);
}

static void	process_word(char **s, t_list **tokens)
{
	t_token	*token;
	char	*value;

	value = read_word((const char **)s);
	token = create_token(TOKEN_WORD, value);
	ft_lstadd_back(tokens, ft_lstnew(token));
}

t_list	*lexer(char *input)
{
	t_list	*tokens;
	char	*s;

	if (!input)
		return (NULL);
	tokens = NULL;
	s = input;
	while (*s)
	{
		while (*s && is_whitespace(*s))
			s++;
		if (!*s)
			break ;
		if ((*s == '|' && process_pipe(&s, &tokens) == 0)
			|| (*s == '<' && process_redirect_in(&s, &tokens) == 0)
			|| (*s == '>' && process_redirect_out(&s, &tokens) == 0))
			continue ;
		if ((*s == '\'' && process_single_quote(&s, &tokens) < 0)
			|| (*s == '\"' && process_double_quote(&s, &tokens) < 0))
			break ;
		process_word(&s, &tokens);
	}
	ft_lstadd_back(&tokens, ft_lstnew(create_token(TOKEN_EOF, NULL)));
	free(input);
	return (tokens);
}
