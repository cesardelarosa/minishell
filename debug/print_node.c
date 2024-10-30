/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_node.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tu_nombre <tu_email@student.42.fr>          +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 12:00:00 by tu_nombre          #+#    #+#            */
/*   Updated: 2024/10/30 13:10:08 by cde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "ast.h"

void	print_node_recursive(t_ast_node *node, int level);

void	print_indentation(int level)
{
	int	i;

	i = 0;
	while (i < level)
	{
		printf("  ");
		i++;
	}
}

void	print_command_args(t_command *cmd, int level)
{
	int	i;

	print_indentation(level);
	printf("Arguments: ");
	i = 0;
	while (cmd->args[i])
	{
		printf("%s ", cmd->args[i]);
		i++;
	}
	printf("\n");
}

void	print_input_redirection(t_file *input, int level)
{
	print_indentation(level);
	printf("Input Redirection: ");
	printf("%s\n", input->file);
}

void	print_output_redirection(t_file *output, int level)
{
	print_indentation(level);
	printf("Output Redirection: ");
	printf("%s\n", output->file);
}

void	print_command(t_command *cmd, int level)
{
	print_indentation(level);
	printf("Command:\n");
	if (cmd->args)
		print_command_args(cmd, level + 1);
	if (cmd->input.file)
		print_input_redirection(&cmd->input, level + 1);
	if (cmd->output.file)
		print_output_redirection(&cmd->output, level + 1);
}

void	print_operator(t_operator *op, int level)
{
	print_indentation(level);
	printf("Operator: ");
	if (op->type == PIPE)
		printf("|\n");
	else if (op->type == AND)
		printf("&&\n");
	else if (op->type == OR)
		printf("||\n");
	if (op->left)
	{
		print_indentation(level);
		printf("Left:\n");
		print_node_recursive(op->left, level + 1);
	}
	if (op->right)
	{
		print_indentation(level);
		printf("Right:\n");
		print_node_recursive(op->right, level + 1);
	}
}

void	print_node_recursive(t_ast_node *node, int level)
{
	if (!node)
		return ;
	if (node->type == COMMAND)
		print_command(&node->u_data.cmd, level);
	else if (node->type == OPERATOR)
		print_operator(&node->u_data.op, level);
}

void	print_node(t_ast_node *root)
{
	print_node_recursive(root, 0);
}
