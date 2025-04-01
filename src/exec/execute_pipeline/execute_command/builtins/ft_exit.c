/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <code@cesardelarosa.xyz>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 21:13:11 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/03/31 21:16:22 by cde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	ft_free_split(argv);
	exit(exit_status);
	return (exit_status);
}
