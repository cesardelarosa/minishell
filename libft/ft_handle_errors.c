/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_errors.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <cde-la-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 09:43:12 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/02/14 13:50:50 by cesi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft.h"

void	ft_handle_errors(char *prog, char *msg, char *cmd, int exit_code)
{
	if (prog)
	{
		ft_putstr_fd(prog, 2);
		ft_putstr_fd(": ", 2);
	}
	if (cmd)
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	exit(exit_code);
}
