/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrian <adrian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 17:48:49 by cde-la-r          #+#    #+#             */
/*   Updated: 2024/10/04 09:19:39 by adrian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "minishell.h"

/*
** Main entry point of the minishell program.
** It displays a welcome message, sets up signal handlers, and then enters
** an infinite loop to handle user input, parse it, and execute commands.
**
** @return: Always returns 0 (although the loop theoretically never ends).
*/
int	main(void)
{
	printf(WELCOME_MSG);
	setup_signal_handlers();
	while (42)
		exec(parser(lexer(read_input())));
	return (0);
}
