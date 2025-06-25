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

static t_envvar	*find_and_update_envvar(t_env *env, const char *key,
		const char *value, int overwrite)
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
			return (curr);
		}
		curr = curr->next;
	}
	return (NULL);
}

static int	append_new_envvar(t_env *env, const char *key, const char *value)
{
	t_envvar	*new_node;
	t_envvar	*last;

	new_node = envvar_new(key, value);
	if (!new_node)
		return (-1);
	if (env->head == NULL)
		env->head = new_node;
	else
	{
		last = env->head;
		while (last->next)
			last = last->next;
		last->next = new_node;
	}
	return (0);
}

int	env_set(t_env *env, const char *key, const char *value, int overwrite)
{
	t_envvar	*existing_var;

	existing_var = find_and_update_envvar(env, key, value, overwrite);
	if (existing_var == NULL)
	{
		if (append_new_envvar(env, key, value) != 0)
			return (-1);
	}
	env_update_envp(env);
	return (0);
}
