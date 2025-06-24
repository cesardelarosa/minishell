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

static int	prepare_heredocs(t_list *redirs)
{
	t_redir	*r;

	while (redirs)
	{
		r = (t_redir *)redirs->content;
		if (r->type == REDIR_HEREDOC)
		{
			r->heredoc_fd = handle_heredoc(r);
			if (r->heredoc_fd < 0)
				return (r->heredoc_fd);
		}
		redirs = redirs->next;
	}
	return (0);
}

static int	apply_redirections(t_list *redirs)
{
	t_redir	*r;
	int		status;

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
		{
			if (dup2(r->heredoc_fd, STDIN_FILENO) < 0)
				status = -1;
		}
		redirs = redirs->next;
	}
	return (status);
}

int	handle_redirs(t_list *redirs)
{
	int	status;
	int	prep_status;

	prep_status = prepare_heredocs(redirs);
	if (prep_status != 0)
	{
		if (prep_status == -2)
			return (130);
		return (-1);
	}
	status = apply_redirections(redirs);
	return (status);
}
