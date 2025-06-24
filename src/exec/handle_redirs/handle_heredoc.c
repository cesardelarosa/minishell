/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <code@cesardelarosa.xyz>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 12:27:40 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/06/24 13:06:05 by cde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"
#include "structs.h"
#include "errors.h"

int	handle_heredoc(t_redir *r)
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
