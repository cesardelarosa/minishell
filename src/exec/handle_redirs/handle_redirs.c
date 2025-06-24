/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <code@cesardelarosa.xyz>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 12:27:28 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/06/21 12:14:00 by cde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "handle_redir.h"
#include "structs.h"
#include "errors.h"
#include <unistd.h>
#include <string.h>
#include <errno.h>

int	handle_redirs(t_list *redirs)
{
	t_redir	*r;
	int		status;

	if (!redirs)
		return (0);
	status = 0;
	while (redirs && status == 0)
	{
		r = (t_redir *)redirs->content;
		if (r->type == REDIR_INPUT)
			status = handle_redir_in(r);
		else if (r->type == REDIR_OUTPUT)
			status = handle_redir_out(r);
		else if (r->type == REDIR_APPEND)
			status = handle_redir_append(r);
		else if (r->type == REDIR_HEREDOC)
			status = handle_heredoc(r);
		redirs = redirs->next;
	}
	return (status);
}
