/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_node.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 14:29:16 by cde-la-r          #+#    #+#             */
/*   Updated: 2024/10/01 17:39:23 by cde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "ast.h"

/*
** Prints the type of the AST node based on its type.
**
** This function outputs a string representation of the node type 
** to the standard output.
**
** @param type: The type of the AST node to print.
*/
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

/*
** Prints the arguments of a command node.
**
** This function iterates over the command arguments and prints 
** them to the standard output.
**
** @param args: The array of arguments to print.
*/
void	print_node_args(char **args)
{
	while (args && *args)
		printf("%s ", *args++);
	printf("\n");
}

/*
** Recursively prints the AST nodes.
**
** This function prints the current node's type and its arguments, 
** then recursively calls itself to print the left and right 
** children nodes with increased depth.
**
** @param node: The current AST node to print.
** @param depth: The current depth in the tree for indentation.
** @param branch: The branch indicator for the output.
*/
void	print_node_recursive(t_ast_node *node, int depth, char *branch)
{
	if (!node)
	{
		printf("%*s%sNULL\n", depth * 4, "", branch);
		return ;
	}
	printf("%*s%s", depth * 4, "", branch);
	if (node->type == NODE_HEREDOC)
		printf("delimiter: %s ", node->delimiter);
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

/*
** Prints the entire AST from the root.
**
** This function starts the printing process, indicating the start 
** of the parsed syntax tree and the execution section.
**
** @param root: The root node of the AST to print.
*/
void	print_node(t_ast_node *root)
{
	printf("Árbol sintáctico parseado:\n \n");
	print_node_recursive(root, 0, "");
	printf("\nEjecución:\n\n");
}
