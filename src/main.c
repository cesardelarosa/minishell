/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrian <adrian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 17:48:49 by cde-la-r          #+#    #+#             */
/*   Updated: 2024/10/30 21:46:31 by cde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "minishell.h"

int	g_exit_status = 0;

/*
** Main entry point of the minishell program.
** It displays a welcome message, sets up signal handlers, and then enters
** an infinite loop to handle user input, parse it, and execute commands.
**
** @return: Always returns 0 (although the loop theoretically never ends).
*/
int	main(int argc, char **argv, char **envp)
{
	t_ast_node	*root;
	(void)argc;
	(void)argv;
	printf(WELCOME_MSG);
	setup_signal_handlers();
	while (42)
	{
		root = parser(lexer(read_input()), envp);
#if DEBUG == 1
		print_node(root);
		printf("\033[38;2;255;105;180mEXECUTION:\033[0m\n");
#endif
		exec(root);
		free_node(root);
#if DEBUG == 1
		printf("\033[38;2;255;105;180mEND EXECUTION\033[0m\n");
		printf("\n\033[38;2;255;165;0mERROR DEBUGGING:\n\t\033[38;2;255;0;0mexit:\033[0m %d\n", g_exit_status);
#endif
	}
	return (0);
}
