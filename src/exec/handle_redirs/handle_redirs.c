/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <code@cesardelarosa.xyz>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 12:27:28 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/04/11 12:22:18 by cesi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "handle_redir.h"

int	handle_redirs(t_list *redirs)
{
	t_redir	*r;
	int		status;

	status = 0;
	while (status == 0 && redirs)
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
