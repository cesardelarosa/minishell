/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_destroy.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <code@cesardelarosa.xyz>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 12:14:56 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/04/03 23:31:42 by cesi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct_creation.h"

void	command_destroy(void *content)
{
	t_command	*cmd;

	cmd = (t_command *)content;
	ft_free_split(cmd->argv);
	ft_lstclear(&cmd->redirs, redir_destroy);
	free(cmd);
}
