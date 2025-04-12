/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_get.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <code@cesardelarosa.xyz>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 00:19:26 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/04/04 00:24:43 by cesi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "libft.h"

char	*env_get(t_env *env, const char *key)
{
	t_envvar	*curr;

	curr = env->head;
	while (curr)
	{
		if (ft_strcmp(curr->key, (char *)key) == 0)
			return (curr->value);
		curr = curr->next;
	}
	return (NULL);
}
