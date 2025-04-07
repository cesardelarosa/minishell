/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_lparen.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <code@cesardelarosa.xyz>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 23:34:07 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/04/07 23:34:08 by cde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"
#include <stdlib.h>

int	process_lparen(char **s, t_list **tokens)
{
	t_token	*token;

	token = create_token(TOKEN_LPAREN, ft_strdup("("), 0);
	ft_lstadd_back(tokens, ft_lstnew(token));
	(*s)++;
	return (0);
}
