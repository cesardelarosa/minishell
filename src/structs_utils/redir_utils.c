/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <code@cesardelarosa.xyz>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 09:27:18 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/06/24 12:20:58 by cde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "struct_creation.h"
#include <stdlib.h>

t_redir	*redir_create(t_redir_type type, char *file, t_command *parent_cmd)
{
	t_redir	*r;

	r = ft_calloc(1, sizeof(t_redir));
	if (!r)
		return (NULL);
	r->type = type;
	r->file = ft_strdup(file);
	if (!r->file)
	{
		free(r);
		return (NULL);
	}
	r->cmd = parent_cmd;
	r->heredoc_buf = NULL;
	return (r);
}

void	redir_destroy(void *content)
{
	t_redir	*r;

	r = (t_redir *)content;
	if (r->heredoc_buf)
		free(r->heredoc_buf);
	free(r->file);
	free(r);
}
