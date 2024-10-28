/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <cde-la-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 16:48:02 by cde-la-r          #+#    #+#             */
/*   Updated: 2024/10/28 16:48:02 by cde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "ast.h"
#include "libft.h"

void	free_file(t_file *file)
{
	if (file->fd != -1)
		close(file->fd);
	if (file->file)
		free(file->file);
}

void	free_command(t_command *cmd)
{
	if (cmd->args)
		ft_free_split(cmd->args);
	free_file(&cmd->input);
	free_file(&cmd->output);
}

void	free_node(t_ast_node *node)
{
	if (!node)
		return ;
	if (node->type == COMMAND)
		free_command(&node->u_data.cmd);
	else if (node->type == OPERATOR)
	{
		if (node->u_data.op.left)
			free_node(node->u_data.op.left);
		if (node->u_data.op.right)
			free_node(node->u_data.op.right);
	}
	free(node);
}
