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

static void	print_env_in_order(t_envvar *curr)
{
	if (!curr)
		return ;
	print_env_in_order(curr->next);
	printf("%s=%s\n", curr->key, curr->value);
}

int	ft_env(char **argv, t_env *env)
{
	(void)argv;
	print_env_in_order(env->head);
	return (0);
}
