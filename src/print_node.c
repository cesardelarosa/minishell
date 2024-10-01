/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_node.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 14:29:16 by cde-la-r          #+#    #+#             */
/*   Updated: 2024/10/01 16:32:41 by cde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "ast.h"

void	print_node_type(int type)
{
	if (type == NODE_COMMAND)
		printf("Command\n");
	else if (type == NODE_PIPE)
		printf("| (PIPE)\n");
	else if (type == NODE_REDIRECTION_IN)
		printf("< (REDIRECTION INPUT)\n");
	else if (type == NODE_REDIRECTION_OUT)
		printf("> (REDIRECTION OUTPUT)\n");
	else if (type == NODE_REDIRECTION_APPEND)
		printf(">> (REDIRECTION APPEND)\n");
	else if (type == NODE_AND)
		printf("&& (AND)\n");
	else if (type == NODE_OR)
		printf("|| (OR)\n");
	else if (type == NODE_HEREDOC)
		printf("<< (HEREDOC)\n");
	else
		printf("Unknown\n");
}

void	print_node_args(char **args)
{
	while (args && *args)
		printf("%s ", *args++);
	printf("\n");
}

void	print_node_recursive(t_ast_node *node, int depth, char *branch)
{
	if (!node)
	{
		printf("%*s%sNULL\n", depth * 4, "", branch);
		return ;
	}
	printf("%*s%s", depth * 4, "", branch);
	if (node->type == NODE_COMMAND)
	{
		printf("Command: ");
		print_node_args(node->args);
	}
	else
		print_node_type(node->type);
	if (node->left)
		print_node_recursive(node->left, depth + 1, "L- ");
	if (node->right)
		print_node_recursive(node->right, depth + 1, "R- ");
}

void	print_node(t_ast_node *root)
{
	printf("Árbol sintáctico parseado:\n \n");
	print_node_recursive(root, 0, "");
	printf("\nEjecución:\n\n");
}
