/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_rparen.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <code@cesardelarosa.xyz>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 23:33:50 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/04/07 23:40:13 by cesi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"
#include <stdlib.h>

int	process_rparen(char **s, t_list **tokens)
{
	t_token	*token;

	token = create_token(TOKEN_RPAREN, ft_strdup(")"), 0);
	ft_lstadd_back(tokens, ft_lstnew(token));
	(*s)++;
	return (0);
}
