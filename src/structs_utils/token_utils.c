/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <code@cesardelarosa.xyz>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 09:44:47 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/06/20 09:44:50 by cde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>

t_token	*create_token(t_token_type type, char *value, int joined)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->value = value;
	token->joined = joined;
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
