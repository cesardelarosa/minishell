/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <code@cesardelarosa.xyz>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 12:27:40 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/04/11 16:36:45 by cde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"
#include "errors.h"
#include "signals.h"
#include "structs.h"
#include <stdio.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>

#define EOF_MSG "warning: here-document delimited by end-of-file\n"

extern volatile sig_atomic_t	g_sigint_received;

static void	read_heredoc_lines(int write_fd, t_redir *redir)
{
	char	*line;
	char	*expanded;

	g_sigint_received = 0;
	while (1)
	{
		line = readline("> ");
		if (!line || g_sigint_received)
		{
			if (!g_sigint_received)
				ft_putstr_fd(EOF_MSG, STDERR_FILENO);
			if (line)
				free(line);
			break ;
		}
		if (ft_strcmp(line, redir->file) == 0)
		{
			free(line);
			break ;
		}
		expanded = env_expand_variables(line, redir->cmd->p->ctx->env);
		free(line);
		if (!expanded)
			break ;
		ft_putendl_fd(expanded, write_fd);
		free(expanded);
	}
	close(write_fd);
	if (g_sigint_received)
		exit(130);
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
	setup_signals(HEREDOC_MODE);
	pid = fork();
	if (pid < 0)
		error_exit_code(1, strerror(errno), "fork", redir->cmd->p);
	if (pid == 0)
	{
		setup_signals(RESET_MODE);
		close(pipefd[0]);
		read_heredoc_lines(pipefd[1], redir);
	}
	else
	{
		close(pipefd[1]);
		waitpid(pid, &status, 0);
		setup_signals(INTERACTIVE_MODE);
		if ((WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
			|| (WIFEXITED(status) && WEXITSTATUS(status) == 130))
			result = 130;
		else if (dup2(pipefd[0], STDIN_FILENO) < 0)
			result = -1;
		close(pipefd[0]);
	}
	return (result);
}
