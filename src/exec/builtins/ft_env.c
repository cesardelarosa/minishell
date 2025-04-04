/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <code@cesardelarosa.xyz>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 10:17:25 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/04/04 10:17:27 by cde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "libft.h"
#include <stdio.h>

static void	print_env_in_order(t_envvar *curr)
{
	if (!curr)
		return ;
	print_env_in_order(curr->next);
	printf("%s=%s\n", curr->key, curr->value);
}

int	ft_env(char **argv, char **envp)
{
	t_env	*env;

	(void)argv;
	env = env_init(envp);
	if (!env)
		return (1);
	print_env_in_order(env->head);
	env_destroy(env);
	return (0);
}
