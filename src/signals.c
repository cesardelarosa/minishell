/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <cde-la-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 13:38:29 by cde-la-r          #+#    #+#             */
/*   Updated: 2024/10/30 13:59:41 by cde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <readline/readline.h>
#include "minishell.h"

/*
** Handles SIGINT by writing a newline and refreshing the readline interface.
**
** @param sign: The signal number received.
*/
void	sigint_handler(int sign)
{
	if (sign == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		print_prompt();
		rl_redisplay();
		g_exit_status = 130;
	}
}

/*
** Sets up signal handlers for the shell.
**
** SIGINT is handled by sigint_handler and SIGQUIT is ignored.
*/
void	setup_signal_handlers(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}
