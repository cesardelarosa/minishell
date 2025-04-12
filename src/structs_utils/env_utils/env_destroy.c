/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_destroy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesi <cesi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 17:48:00 by cesi              #+#    #+#             */
/*   Updated: 2025/04/04 17:48:00 by cesi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "env.h"
#include <stdlib.h>

void	env_destroy(t_env *env)
{
	t_envvar	*curr;
	t_envvar	*next;

	if (!env)
		return ;
	curr = env->head;
	while (curr)
	{
		next = curr->next;
		free(curr->key);
		free(curr->value);
		free(curr);
		curr = next;
	}
	if (env->envp)
		ft_free_split(env->envp);
	free(env);
}
