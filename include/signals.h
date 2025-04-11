/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <code@cesardelarosa.xyz>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 11:35:33 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/04/11 11:35:40 by cde-la-r         ###   ########.fr       */
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

#endif
