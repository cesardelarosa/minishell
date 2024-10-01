/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 14:08:36 by cde-la-r          #+#    #+#             */
/*   Updated: 2024/10/01 14:30:13 by cde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "libft.h"
#include "minishell.h"
#include "ast.h"

t_ast_node	*create_node(t_node_type type, char **args)
{
	t_ast_node	*new_node;

	new_node = (t_ast_node *)malloc(sizeof(t_ast_node));
	if (!new_node)
		return (NULL);
	new_node->type = type;
	new_node->args = args;
	if (args && !new_node->args)
	{
		free(new_node);
		return (NULL);
	}
	new_node->left = NULL;
	new_node->right = NULL;
	return (new_node);
}

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
	free(node);
}
