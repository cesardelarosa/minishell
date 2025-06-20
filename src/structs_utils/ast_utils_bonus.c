/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <code@cesardelarosa.xyz>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 09:39:02 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/06/20 13:00:55 by cde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast_utils_bonus.h"
#include "libft.h"
#include "struct_creation.h"
#include <stdlib.h>

t_ast	*ast_create(t_ast_type type, t_ast *left, t_ast *right,
		char *pipeline_str, t_ctx *ctx)
{
	t_ast	*node;

	node = malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	node->type = type;
	node->left = left;
	node->right = right;
	node->pipeline_str = pipeline_str;
	node->ctx = ctx;
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
	if (ast->pipeline_str)
		free(ast->pipeline_str);
	free(ast);
}
