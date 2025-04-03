/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_array.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <code@cesardelarosa.xyz>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 00:20:45 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/04/04 00:20:47 by cde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "libft.h"
#include <stdlib.h>

static int	count_vars(t_env *env)
{
	int			count;
	t_envvar	*curr;

	count = 0;
	curr = env->head;
	while (curr)
	{
		count++;
		curr = curr->next;
	}
	return (count);
}

char	**env_to_array(t_env *env)
{
	char		**array;
	t_envvar	*curr;
	int			i;
	char		*tmp;

	i = 0;
	array = malloc(sizeof(char *) * (count_vars(env) + 1));
	if (!array)
		return (NULL);
	curr = env->head;
	while (curr)
	{
		tmp = ft_strjoin(curr->key, "=");
		array[i] = ft_strjoin(tmp, curr->value);
		free(tmp);
		i++;
		curr = curr->next;
	}
	array[i] = NULL;
	return (array);
}
