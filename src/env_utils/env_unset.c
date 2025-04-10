/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <code@cesardelarosa.xyz>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 00:20:16 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/04/04 00:24:21 by cesi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "libft.h"
#include <stdlib.h>

int	env_unset(t_env *env, const char *key)
{
	t_envvar	*curr;
	t_envvar	*prev;

	curr = env->head;
	prev = NULL;
	while (curr)
	{
		if (ft_strcmp(curr->key, (char *)key) == 0)
		{
			if (prev)
				prev->next = curr->next;
			else
				env->head = curr->next;
			free(curr->key);
			free(curr->value);
			free(curr);
			env_update_envp(env);
			return (0);
		}
		prev = curr;
		curr = curr->next;
	}
	return (0);
}
