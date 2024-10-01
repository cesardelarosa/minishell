/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 13:14:30 by cde-la-r          #+#    #+#             */
/*   Updated: 2024/10/01 17:37:59 by cde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"
#include "parser_utils.h"

/*
** Parses an array of tokens into an abstract syntax tree (AST).
**
** This function recursively processes the tokens to create nodes
** based on the highest precedence operator found within the specified
** range of tokens.
**
** @param tokens: The array of tokens to parse.
** @param start: The starting index of the range to parse.
** @param end: The ending index of the range to parse.
** @return: A pointer to the root of the AST node created.
*/
t_ast_node	*parse_tokens(char **tokens, int start, int end)
{
	int			op_pos;
	t_ast_node	*node;
	t_node_type	op_type;

	if (start > end)
		return (NULL);
	op_pos = find_highest_operator(tokens, start, end);
	if (op_pos != -1 && op_pos >= start && op_pos <= end)
	{
		op_type = get_operator_type(tokens[op_pos]);
		node = create_node(op_type, NULL);
		node->left = parse_tokens(tokens, start, op_pos - 1);
		node->right = parse_tokens(tokens, op_pos + 1, end);
	}
	else
		node = create_node(NODE_COMMAND, dup_args_range(tokens, start, end));
	return (node);
}

/*
** Parses the entire array of tokens to generate an AST.
**
** This function calculates the length of the tokens array, invokes
** the parsing function to create the AST, and frees the original
** tokens array.
**
** @param tokens: The array of tokens to parse.
** @return: A pointer to the root of the AST created.
*/
t_ast_node	*parser(char **tokens)
{
	int			len;
	t_ast_node	*root;

	len = 0;
	while (tokens[len])
		len++;
	root = parse_tokens(tokens, 0, len - 1);
	ft_free_split(tokens);
	return (root);
}
