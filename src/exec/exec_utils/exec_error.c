/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <code@cesardelarosa.xyz>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 12:15:06 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/04/03 19:25:44 by cde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct_creation.h"
#include <stdlib.h>

void	error_exit_code(int code, char *msg, char *target, t_pipeline *p)
{
	if (target)
	{
		ft_putstr_fd(target, 2);
		ft_putstr_fd(": ", 2);
	}
	if (msg)
	{
		ft_putstr_fd(msg, 2);
		ft_putchar_fd('\n', 2);
	}
	if (p)
		pipeline_destroy(p);
	exit(code);
}
