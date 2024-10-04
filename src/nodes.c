/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 14:08:36 by cde-la-r          #+#    #+#             */
/*   Updated: 2024/10/01 17:47:17 by cde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "libft.h"
#include "minishell.h"
#include "ast.h"

/*
** Creates a new AST node of the specified type, initializing its
** arguments and left/right child pointers. Returns a pointer to the
** newly created node, or NULL if memory allocation fails.
**
** @param type: The type of the node to create.
** @param args: The arguments associated with the node.
** @return: A pointer to the newly created node, or NULL on failure.
*/
t_ast_node	*create_node(t_node_type type, char **args)
{
	t_ast_node	*new_node;

	new_node = (t_ast_node *)malloc(sizeof(t_ast_node));
	if (!new_node)
		return (NULL);
	new_node->type = type;
	if (type == NODE_HEREDOC)
	{
		if (args && *args)
			new_node->delimiter = ft_strdup(*args);
		else
			new_node->delimiter = NULL;
		new_node->args = NULL;
	}
	else
	{
		new_node->args = args;
		new_node->delimiter = NULL;
	}
	new_node->left = NULL;
	new_node->right = NULL;
	return (new_node);
}

/*
** Frees the memory allocated for the specified AST node and its children.
** If the node has associated arguments, they are also freed.
**
** @param node: The AST node to free.
*/
void	free_node(t_ast_node *node)
{
	if (!node)
		return ;
	free_node(node->left);
	free_node(node->right);
	if (node->args)
	{
		ft_free_split(node->args);
		node->args = NULL;
	}
	if (node->delimiter)
	{
		free(node->delimiter);
		node->delimiter = NULL;
	}
	free(node);
}
