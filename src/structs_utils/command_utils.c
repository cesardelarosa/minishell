/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <code@cesardelarosa.xyz>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 09:29:07 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/06/25 00:30:31 by cde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct_creation.h"
#include <stdlib.h>

t_command	*command_create(char *cmd_str)
{
	t_command	*cmd;

	(void)cmd_str;
	cmd = ft_calloc(1, sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->argv = NULL;
	cmd->redirs = NULL;
	cmd->p = NULL;
	return (cmd);
}

void	command_destroy(void *content)
{
	t_command	*cmd;

	cmd = (t_command *)content;
	ft_free_split(cmd->argv);
	ft_lstclear(&cmd->redirs, redir_destroy);
	free(cmd);
}

int	command_add_redir(t_command *cmd, t_token_type type, char *file)
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
