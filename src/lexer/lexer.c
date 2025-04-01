/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <code@cesardelarosa.xyz>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 17:20:26 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/04/01 11:58:30 by cesi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "lexer_utils.h"
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>

static int	is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
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
		if (!*s || (*s == '\'' && process_single_quote(&s, &tokens) < 0)
			|| (*s == '\"' && process_double_quote(&s, &tokens) < 0))
			break ;
		if ((*s == '|' && process_pipe(&s, &tokens) == 0)
			|| (*s == '<' && process_redirect_in(&s, &tokens) == 0)
			|| (*s == '>' && process_redirect_out(&s, &tokens) == 0)
			|| (*s == '$' && process_variable(&s, &tokens) == 0))
			continue ;
		process_word(&s, &tokens);
	}
	ft_lstadd_back(&tokens, ft_lstnew(create_token(TOKEN_EOF, NULL)));
	free(input);
	return (tokens);
}
