/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_operator.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <code@cesardelarosa.xyz>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 17:20:26 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/03/31 23:45:56 by cesi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>

int	process_pipe(char **s, t_list **tokens)
{
	t_token	*token;

	token = create_token(TOKEN_PIPE, ft_strdup("|"));
	ft_lstadd_back(tokens, ft_lstnew(token));
	(*s)++;
	return (0);
}

int	process_redirect_in(char **s, t_list **tokens)
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

int	process_redirect_out(char **s, t_list **tokens)
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
