/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <code@cesardelarosa.xyz>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 21:13:11 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/04/03 13:06:04 by cde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/history.h>
#include <readline/readline.h>
#include "libft.h"
#include <stdlib.h>

int	ft_exit(char **argv, char **envp)
{
	int	exit_status;

	(void)envp;
	exit_status = 0;
	if (argv[1])
		exit_status = ft_atoi(argv[1]);
	ft_printf("Exiting minishell...\n");
	rl_clear_history();
	exit(exit_status);
	return (exit_status);
}
