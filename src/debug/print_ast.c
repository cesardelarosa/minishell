/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <code@cesardelarosa.xyz>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 11:07:30 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/04/08 11:07:31 by cde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include <stdio.h>

static const char	*ast_type_to_str(int type)
{
	if (type == AST_PIPE)
		return ("Pipe");
	else if (type == AST_AND)
		return ("And");
	else if (type == AST_OR)
		return ("Or");
	else if (type == AST_GROUP)
		return ("Group");
	else
		return ("Unknown");
}

static void	print_indent(int indent)
{
	int	i;

	i = 0;
	while (i < indent)
	{
		printf("  ");
		i++;
	}
}

void	print_command(t_command *cmd, int indent)
{
	int	i;

	if (!cmd || !cmd->argv)
		return ;
	print_indent(indent);
	printf("Command: ");
	i = 0;
	while (cmd->argv[i])
	{
		printf("%s ", cmd->argv[i]);
		i++;
	}
	printf("\n");
}

void	print_pipeline(t_pipeline *pipeline, int indent)
{
	t_list	*current;

	if (!pipeline)
		return ;
	print_indent(indent);
	printf("Pipeline with %u commands\n", pipeline->cmd_count);
	current = pipeline->commands;
	while (current)
	{
		print_command((t_command *)current->content, indent + 1);
		current = current->next;
	}
}

void	print_ast(t_ast *ast, int indent)
{
	if (!ast)
	{
		printf("NO HAY AST\n");
		return ;
	}
	print_indent(indent);
	printf("Node: %s\n", ast_type_to_str(ast->type));
	if (ast->type == AST_PIPE && ast->pipeline)
	{
		print_indent(indent + 1);
		printf("Pipeline:\n");
		print_pipeline(ast->pipeline, indent + 2);
	}
	if (ast->left)
	{
		print_indent(indent);
		printf("Left:\n");
		print_ast(ast->left, indent + 1);
	}
	if (ast->right)
	{
		print_indent(indent);
		printf("Right:\n");
		print_ast(ast->right, indent + 1);
	}
}
