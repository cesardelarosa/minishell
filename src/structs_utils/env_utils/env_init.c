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

static t_envvar	*create_envvar_from_str(const char *env_str)
{
	t_envvar	*node;
	char		*eq;
	char		*key;
	char		*value;

	eq = ft_strchr(env_str, '=');
	if (!eq)
		return (NULL);
	key = ft_substr(env_str, 0, eq - env_str);
	if (!key)
		return (NULL);
	value = ft_strdup(eq + 1);
	if (!value)
	{
		free(key);
		return (NULL);
	}
	node = malloc(sizeof(t_envvar));
	if (node)
	{
		node->key = key;
		node->value = value;
		node->next = NULL;
	}
	return (node);
}

static void	populate_env_list(t_env *env, char **envp)
{
	int			i;
	t_envvar	*new_node;
	t_envvar	*last;

	last = NULL;
	i = 0;
	while (envp[i])
	{
		new_node = create_envvar_from_str(envp[i]);
		if (new_node)
		{
			if (env->head == NULL)
				env->head = new_node;
			else
				last->next = new_node;
			last = new_node;
		}
		i++;
	}
}

t_env	*env_init(char **envp)
{
	t_env	*env;

	env = malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	env->head = NULL;
	env->envp = NULL;
	populate_env_list(env, envp);
	env_update_envp(env);
	return (env);
}
