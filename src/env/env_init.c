/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <code@cesardelarosa.xyz>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 00:19:05 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/04/04 00:23:12 by cesi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "libft.h"
#include <stdlib.h>
#include <string.h>

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

static t_envvar	*create_envvar_from_str(const char *env_str)
{
	char		*eq;
	char		*key;
	char		*value;
	t_envvar	*node;

	eq = ft_strchr(env_str, '=');
	if (!eq)
		return (NULL);
	key = ft_substr(env_str, 0, eq - env_str);
	value = ft_strdup(eq + 1);
	node = envvar_new(key, value);
	free(key);
	free(value);
	return (node);
}

t_env	*env_init(char **envp)
{
	t_env		*env;
	t_envvar	*node;
	int			i;

	env = malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	env->head = NULL;
	i = 0;
	while (envp[i])
	{
		node = create_envvar_from_str(envp[i]);
		if (node)
		{
			node->next = env->head;
			env->head = node;
		}
		i++;
	}
	return (env);
}
