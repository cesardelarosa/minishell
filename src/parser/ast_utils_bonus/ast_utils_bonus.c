/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <code@cesardelarosa.xyz>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 12:19:06 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/04/12 12:15:04 by cesi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast_utils_bonus.h"
#include "libft.h"
#include "struct_creation.h"
#include <stdlib.h>

t_ast	*ast_create(int type, t_ast *left, t_ast *right, t_pipeline *pipeline)
{
	t_ast	*node;

	node = malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	node->type = type;
	node->left = left;
	node->right = right;
	node->pipeline = pipeline;
	return (node);
}

void	ast_destroy(t_ast *ast)
{
	if (!ast)
		return ;
	if (ast->left)
		ast_destroy(ast->left);
	if (ast->right)
		ast_destroy(ast->right);
	free(ast);
}
