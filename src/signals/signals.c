/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <code@cesardelarosa.xyz>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 18:40:38 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/03/29 19:28:30 by cesi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include "libft.h"

volatile sig_atomic_t	g_sigint_received = 0;

char	*build_prompt(char **envp);

static void sigint_handler(int signum)
{
	(void)signum;

	g_sigint_received = 1;
	rl_replace_line("", 0);
	rl_on_new_line();
	write(STDOUT_FILENO, "\n", 1);
	rl_redisplay();
}

void init_signals(void)
{
	struct sigaction sa;

	sa.sa_handler = sigint_handler;
	sa.sa_mask = (sigset_t){0};
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}
