/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_add_redir.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <code@cesardelarosa.xyz>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 12:14:56 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/04/03 23:30:50 by cesi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct_creation.h"

int	command_add_redir(t_command *cmd, t_redir_type type, char *file)
{
	t_redir	*r;
	t_list	*node;

	if (!cmd)
		return (0);
	r = redir_create(type, file, cmd);
	if (!r)
		return (0);
	node = ft_lstnew(r);
	if (!node)
	{
		redir_destroy(r);
		return (0);
	}
	ft_lstadd_back(&cmd->redirs, node);
	return (1);
}
