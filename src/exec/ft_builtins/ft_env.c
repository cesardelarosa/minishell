/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <code@cesardelarosa.xyz>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 10:17:25 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/04/04 10:58:33 by cde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "libft.h"
#include <stdio.h>

int	ft_env(char **argv, t_env *env)
{
	t_envvar	*current;

	if (argv && argv[1])
	{
		ft_putstr_fd("minishell: env: too many arguments\n", 2);
		return (1);
	}
	current = env->head;
	while (current)
	{
		if (current->value)
			printf("%s=%s\n", current->key, current->value);
		current = current->next;
	}
	return (0);
}
