/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <code@cesardelarosa.xyz>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 12:27:40 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/03/09 15:21:40 by cde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"
#include "structs.h"
#include "errors.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>

static int	g_heredoc_sigint = 0;

static void	heredoc_signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		g_heredoc_sigint = 1;
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		close(STDIN_FILENO);
	}
}

static void	setup_heredoc_signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = heredoc_signal_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}

static void	restore_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

static void	read_heredoc_lines(int write_fd, t_redir *redir)
{
	char	*line;

	setup_heredoc_signals();
	while (1)
	{
		line = readline("> ");
		if (!line || g_heredoc_sigint)
		{
			if (!g_heredoc_sigint && !line)
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
	exit(g_heredoc_sigint);
}

int	handle_heredoc(t_redir *redir)
{
	int		pipefd[2];
	pid_t	pid;
	int		status;

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
		signal(SIGINT, SIG_IGN);
		waitpid(pid, &status, 0);
		restore_signals();
		if (WIFEXITED(status) && WEXITSTATUS(status) == 1)
		{
			close(pipefd[0]);
			return (-1);
		}
		if (dup2(pipefd[0], STDIN_FILENO) < 0)
		{
			close(pipefd[0]);
			return (-1);
		}
		close(pipefd[0]);
	}
	return (0);
}
