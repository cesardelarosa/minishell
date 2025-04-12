/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_and.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <code@cesardelarosa.xyz>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 23:34:39 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/04/12 11:03:17 by cesi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"
#include <stdlib.h>

int	process_and(char **s, t_list **tokens)
{
	t_token	*token;

	token = create_token(TOKEN_AND, ft_strdup("&&"), 0);
	ft_lstadd_back(tokens, ft_lstnew(token));
	(*s) += 2;
	return (0);
}
