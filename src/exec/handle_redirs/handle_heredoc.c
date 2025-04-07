/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <code@cesardelarosa.xyz>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 12:27:40 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/04/07 14:40:16 by cesi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"
#include "structs.h"
#include "errors.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

static void	read_heredoc_lines(int write_fd, t_redir *redir)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			ft_putstr_fd("warning: here-document delimited by end-of-file\n",
				STDERR_FILENO);
			break ;
		}
		if (ft_strcmp(line, redir->file) == 0)
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, write_fd);
		free(line);
	}
	close(write_fd);
	exit(0);
}

int	handle_heredoc(t_redir *redir)
{
	int		pipefd[2];
	pid_t	pid;
	int		status;
	int		result;

	result = 0;
	if (pipe(pipefd) < 0)
		error_exit_code(1, strerror(errno), "pipe", redir->cmd->p);
	pid = fork();
	if (pid < 0)
		error_exit_code(1, strerror(errno), "fork", redir->cmd->p);
	if (pid == 0)
	{
		close(pipefd[0]);
		read_heredoc_lines(pipefd[1], redir);
	}
	else
	{
		close(pipefd[1]);
		waitpid(pid, &status, 0);
		if (dup2(pipefd[0], STDIN_FILENO) < 0)
			result = -1;
		close(pipefd[0]);
	}
	return (result);
}
