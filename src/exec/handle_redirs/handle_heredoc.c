/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <code@cesardelarosa.xyz>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 12:27:40 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/06/21 11:46:39 by cde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"
#include "errors.h"
#include "signals.h"
#include "struct_creation.h"
#include "structs.h"
#include <stdio.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>
#include <stdbool.h>

#define EOF_MSG "warning: here-document delimited by end-of-file\n"

extern volatile sig_atomic_t	g_sigint_received;

int								destroy_ctx(t_ctx *ctx);

static void	cleanup_heredoc(int write_fd, t_redir *redir)
{
	close(write_fd);
	rl_clear_history();
	destroy_ctx(redir->cmd->p->ctx);
	pipeline_destroy(redir->cmd->p);
	if (g_sigint_received)
		exit(130);
	exit(0);
}

static bool	process_line(char *line, int write_fd, t_redir *redir)
{
	char	*expanded;

	expanded = env_expand_variables(line, redir->cmd->p->ctx->env);
	free(line);
	if (!expanded)
		return (false);
	ft_putendl_fd(expanded, write_fd);
	free(expanded);
	return (true);
}

static void	read_heredoc_lines(int write_fd, t_redir *redir)
{
	char	*line;

	g_sigint_received = 0;
	while (1)
	{
		line = readline("> ");
		if (!line || g_sigint_received)
		{
			if (!g_sigint_received)
				ft_putstr_fd(EOF_MSG, STDERR_FILENO);
			free(line);
			break ;
		}
		if (ft_strcmp(line, redir->file) == 0)
		{
			free(line);
			break ;
		}
		if (!process_line(line, write_fd, redir))
			break ;
	}
	cleanup_heredoc(write_fd, redir);
}

static void	heredoc_child(int pipefd[], t_redir *redir)
{
	close(pipefd[0]);
	setup_signals(RESET_MODE);
	read_heredoc_lines(pipefd[1], redir);
}

int	handle_heredoc(t_redir *redir)
{
	int		pipefd[2];
	pid_t	pid;
	int		status;

	if (pipe(pipefd) < 0)
		error_exit_code(1, strerror(errno), "pipe", redir->cmd->p);
	setup_signals(HEREDOC_MODE);
	pid = fork();
	if (pid < 0)
		error_exit_code(1, strerror(errno), "fork", redir->cmd->p);
	if (pid == 0)
		heredoc_child(pipefd, redir);
	close(pipefd[1]);
	waitpid(pid, &status, 0);
	setup_signals(INTERACTIVE_MODE);
	if ((WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		|| (WIFEXITED(status) && WEXITSTATUS(status) == 130))
	{
		close(pipefd[0]);
		return (-2);
	}
	return (pipefd[0]);
}
