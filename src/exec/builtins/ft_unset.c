/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <code@cesardelarosa.xyz>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 10:28:19 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/04/04 11:08:46 by cde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "libft.h"
#include <stdio.h>

int	ft_unset(char **argv, t_env *env)
{
	int		i;
	int		status;

	status = 0;
	i = 1;
	while (argv[i])
	{
		if (env_unset(env, argv[i]) != 0)
			status = 1;
		i++;
	}
	return (status);
}
