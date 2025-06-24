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

static int	apply_heredoc_redir(t_redir *r)
{
	int	pipefd[2];

	if (pipe(pipefd) < 0)
	{
		error_exit_code(1, strerror(errno), "pipe", r->cmd->p);
		return (-1);
	}
	if (r->heredoc_buf)
		write(pipefd[1], r->heredoc_buf, ft_strlen(r->heredoc_buf));
	close(pipefd[1]);
	if (dup2(pipefd[0], STDIN_FILENO) < 0)
	{
		close(pipefd[0]);
		error_exit_code(1, strerror(errno), "dup2", r->cmd->p);
		return (-1);
	}
	close(pipefd[0]);
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
			status = apply_heredoc_redir(r);
		redirs = redirs->next;
	}
	return (status);
}

int	handle_redirs(t_list *redirs)
{
	if (!redirs)
		return (0);
	return (apply_redirections(redirs));
}
