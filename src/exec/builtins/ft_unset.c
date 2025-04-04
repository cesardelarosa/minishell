/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <code@cesardelarosa.xyz>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 10:28:19 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/04/04 10:28:54 by cde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "libft.h"
#include <stdio.h>

int	ft_unset(char **argv, char **envp)
{
	t_env	*env;
	int		i;
	int		status;

	env = env_init(envp);
	if (!env)
		return (1);
	status = 0;
	i = 1;
	while (argv[i])
	{
		if (env_unset(env, argv[i]) != 0)
			status = 1;
		i++;
	}
	env_destroy(env);
	return (status);
}
