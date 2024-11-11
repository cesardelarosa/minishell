/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_node.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 15:30:32 by cde-la-r          #+#    #+#             */
/*   Updated: 2024/10/30 20:56:22 by cde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdbool.h>
#include "ast.h"

#define RESET       "\033[0m"
#define RED         "\033[38;2;255;69;0m"      // Orange Red
#define GREEN       "\033[38;2;50;205;50m"     // Lime Green
#define BLUE        "\033[38;2;30;144;255m"    // Dodger Blue
#define MAGENTA     "\033[38;2;255;20;147m"    // Deep Pink
#define CYAN        "\033[38;2;0;255;255m"     // Aqua
#define YELLOW      "\033[38;2;255;215;0m"     // Gold
#define WHITE       "\033[38;2;255;255;255m"   // Blanco puro

void	print_node_recursive(t_ast_node *node, int level, bool *is_last);

void	print_indentation(int level, bool *is_last)
{
	int	i;

	i = 0;
	while (i < level - 1)
	{
		if (is_last[i++])
			printf("     ");
		else
			printf("│    ");
	}
	if (level > 0)
	{
		if (is_last[level - 1])
			printf("└─── ");
		else
			printf("├─── ");
	}
}

void	print_command_args(t_command *cmd, int level, bool *is_last)
{
	int	i;

	print_indentation(level, is_last);
	printf(CYAN "Arguments: " RESET);
	i = 0;
	while (cmd->args[i])
		printf("%s ", cmd->args[i++]);
	printf("\n");
}

void	print_input_redirection(t_file *input, int level, bool *is_last)
{
	print_indentation(level, is_last);
	printf(GREEN "Input Redirection: " RESET "%s\n", input->file);
}

void	print_output_redirection(t_file *output, int level, bool *is_last)
{
	print_indentation(level, is_last);
	printf(GREEN "Output Redirection: " RESET "%s\n", output->file);
}

void	print_command(t_command *cmd, int level, bool *is_last)
{
	int	child_count;
	int	child_index;

	print_indentation(level, is_last);
	printf(BLUE "Command\n" RESET);
	child_count = 0;
	if (cmd->args)
		child_count++;
	if (cmd->input.file)
		child_count++;
	if (cmd->output.file)
		child_count++;
	child_index = 0;
	if (cmd->args)
	{
		is_last[level] = (child_index == child_count - 1);
		print_command_args(cmd, level + 1, is_last);
		child_index++;
	}
	if (cmd->input.file)
	{
		is_last[level] = (child_index == child_count - 1);
		print_input_redirection(&cmd->input, level + 1, is_last);
		child_index++;
	}
	if (cmd->output.file)
	{
		is_last[level] = (child_index == child_count - 1);
		print_output_redirection(&cmd->output, level + 1, is_last);
		child_index++;
	}
}

void	print_operator(t_operator *op, int level, bool *is_last)
{
	int	child_count;
	int	child_index;

	print_indentation(level, is_last);
	printf(MAGENTA "Operator: " RESET);
	if (op->type == PIPE)
		printf("|");
	else if (op->type == AND)
		printf("&&");
	else if (op->type == OR)
		printf("||");
	printf("\n");
	child_count = 0;
	if (op->left)
		child_count++;
	if (op->right)
		child_count++;
	child_index = 0;
	if (op->left)
	{
		is_last[level] = (child_index == child_count - 1);
		print_node_recursive(op->left, level + 1, is_last);
		child_index++;
	}
	if (op->right)
	{
		is_last[level] = (child_index == child_count - 1);
		print_node_recursive(op->right, level + 1, is_last);
		child_index++;
	}
}

void	print_node_recursive(t_ast_node *node, int level, bool *is_last)
{
	if (!node)
		return ;
	if (node->type == COMMAND)
		print_command(&node->u_data.cmd, level, is_last);
	else if (node->type == OPERATOR)
		print_operator(&node->u_data.op, level, is_last);
}

void	print_node(t_ast_node *root)
{
	bool	is_last[128] = {false};

	printf("\n" YELLOW "PARSER DEBUGGING:\n" RESET);
	print_node_recursive(root, 0, is_last);
	printf("\n");
}
