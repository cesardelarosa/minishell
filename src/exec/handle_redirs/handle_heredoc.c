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

void		init_signals(void);
extern volatile sig_atomic_t	g_sigint_received;

static void	sig_ignore(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

static void	heredoc_signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		g_sigint_received = 1;
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		exit(130);  // Exit immediately on SIGINT
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
	// Re-initialize the main shell's signals
	init_signals();
}

static void	read_heredoc_lines(int write_fd, t_redir *redir)
{
	char	*line;

	setup_heredoc_signals();
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			ft_putstr_fd("warning: here-document delimited by end-of-file\n", 
				STDERR_FILENO);
			break;
		}
		if (ft_strcmp(line, redir->file) == 0)
		{
			free(line);
			break;
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
		sig_ignore();
		waitpid(pid, &status, 0);
		
		// Check if terminated by signal (SIGINT)
		if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		{
			close(pipefd[0]);
			g_sigint_received = 1;
			result = -1;
		}
		// Or if exited with code 130 (our own exit after SIGINT)
		else if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
		{
			close(pipefd[0]);
			g_sigint_received = 1;
			result = -1;
		}
		else if (dup2(pipefd[0], STDIN_FILENO) < 0)
		{
			close(pipefd[0]);
			result = -1;
		}
		close(pipefd[0]);
		restore_signals();
	}
	return (result);
}
