/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_redirect_in.c                              :+:      :+:    :+:   */
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

int	process_redirect_in(char **s, t_list **tokens)
{
	t_token	*token;

	if ((*s)[1] == '<')
	{
		token = create_token(TOKEN_HEREDOC, ft_strdup("<<"), 0);
		ft_lstadd_back(tokens, ft_lstnew(token));
		(*s) += 2;
	}
	else
	{
		token = create_token(TOKEN_REDIRECT_IN, ft_strdup("<"), 0);
		ft_lstadd_back(tokens, ft_lstnew(token));
		(*s)++;
	}
	return (0);
}
