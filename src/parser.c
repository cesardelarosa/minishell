/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrian <adrian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 13:14:30 by cde-la-r          #+#    #+#             */
/*   Updated: 2024/10/04 17:11:01 by adrian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"
#include "parser_utils.h"
#include <stdio.h>

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
t_ast_node	*parse_tokens(char **tokens, int start, int end, char **envp)
{
	int			op_pos;
	t_ast_node	*node;
	t_node_type	op_type;

	if (start > end)
		return (NULL);
	op_pos = find_highest_operator(tokens, start, end);
	op_type = get_operator_type(tokens[op_pos]);
	if (op_type == COMMAND)
		node = create_node(COMMAND, dup_args_range(tokens, start, end), envp);
	else if (op_type == HEREDOC)
	{
		if (op_pos + 1 > end)
		{
			perror("minishell: syntax error near unexpected token 'newline'");
			return (NULL);
		}
		node = create_node(op_type, &tokens[op_pos + 1], envp);
	}
	else
		node = create_node(op_type, NULL, envp);
	node->left = parse_tokens(tokens, start, op_pos - 1, envp);
	node->right = parse_tokens(tokens,
			op_pos + 1 + (op_type == HEREDOC), end, envp);
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
t_ast_node	*parser(char **tokens, char **envp)
{
	int			len;
	t_ast_node	*root;

	if (!tokens)
		return (NULL);
	len = 0;
	while (tokens[len])
		len++;
	root = parse_tokens(tokens, 0, len - 1, envp);
	ft_free_split(tokens);
	return (root);
}
