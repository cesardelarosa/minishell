/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_create_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <code@cesardelarosa.xyz>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 12:19:06 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/06/18 11:41:01 by cesi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast_utils_bonus.h"
#include "libft.h"
#include "struct_creation.h"
#include <stdlib.h>

t_ast	*ast_create(t_ast_type type, t_ast *left, t_ast *right,
		char *pipeline_str)
{
	t_ast	*node;

	node = malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	node->type = type;
	node->left = left;
	node->right = right;
	node->pipeline_str = pipeline_str;
	return (node);
}
