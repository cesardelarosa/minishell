/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <code@cesardelarosa.xyz>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 00:19:49 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/04/04 00:24:01 by cesi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "libft.h"
#include <stdlib.h>

static t_envvar	*envvar_new(const char *key, const char *value)
{
	t_envvar	*node;

	node = malloc(sizeof(t_envvar));
	if (!node)
		return (NULL);
	node->key = ft_strdup(key);
	node->value = ft_strdup(value);
	node->next = NULL;
	return (node);
}

int	env_set(t_env *env, const char *key, const char *value, int overwrite)
{
	t_envvar	*curr;

	curr = env->head;
	while (curr)
	{
		if (ft_strcmp(curr->key, (char *)key) == 0)
		{
			if (overwrite)
			{
				free(curr->value);
				curr->value = ft_strdup(value);
			}
			return (0);
		}
		curr = curr->next;
	}
	curr = envvar_new(key, value);
	if (!curr)
		return (-1);
	curr->next = env->head;
	env->head = curr;
	return (0);
}
