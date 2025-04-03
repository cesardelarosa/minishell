/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_add_command.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <code@cesardelarosa.xyz>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 12:16:25 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/04/03 23:31:59 by cesi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct_creation.h"

int	pipeline_add_command(t_pipeline *p, t_command *cmd)
{
	t_list	*node;

	if (!cmd)
		return (0);
	node = ft_lstnew(cmd);
	if (!node)
	{
		command_destroy(cmd);
		return (0);
	}
	ft_lstadd_back(&p->commands, node);
	p->cmd_count++;
	cmd->p = p;
	return (1);
}
