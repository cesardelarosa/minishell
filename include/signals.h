/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <code@cesardelarosa.xyz>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 11:35:33 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/06/25 00:59:36 by cde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include <signal.h>

typedef enum e_signal_mode
{
	INTERACTIVE_MODE,
	HEREDOC_MODE,
	COMMAND_MODE,
	RESET_MODE
}		t_signal_mode;

void	setup_signals(t_signal_mode mode);
void	interactive_sigint_handler(int sig);
void	heredoc_sigint_handler(int sig);

extern volatile sig_atomic_t	g_sigint_received;

#endif
