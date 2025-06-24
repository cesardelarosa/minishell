/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <code@cesardelarosa.xyz>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 11:35:53 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/06/24 13:06:18 by cde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

volatile sig_atomic_t	g_sigint_received = 0;

void	interactive_sigint_handler(int sig)
{
	(void)sig;
	g_sigint_received = 0;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	heredoc_sigint_handler(int sig)
{
	(void)sig;
	g_sigint_received = 1;
	rl_done = 1;
}

static void	command_sigint_handler(int sig)
{
	(void)sig;
	g_sigint_received = 0;
	write(STDOUT_FILENO, "\n", 1);
}

void	setup_signals(t_signal_mode mode)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	if (mode == RESET_MODE)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		return ;
	}
	if (mode == INTERACTIVE_MODE)
		sa.sa_handler = interactive_sigint_handler;
	else if (mode == HEREDOC_MODE)
		sa.sa_handler = heredoc_sigint_handler;
	else if (mode == COMMAND_MODE)
		sa.sa_handler = command_sigint_handler;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}
