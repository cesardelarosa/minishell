/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+    */
/*   By: cesi <cesi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 17:45:00 by cesi              #+#    #+#             */
/*   Updated: 2025/04/04 17:45:00 by cesi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>

static int	env_count(t_env *env)
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

static void	print_exported_var(t_envvar *var)
{
	printf("declare -x %s=\"%s\"\n", var->key, var->value);
}

static void	sort_env_array(t_envvar **sorted, int count)
{
	int			i;
	int			j;
	t_envvar	*temp;

	i = 0;
	while (i < count - 1)
	{
		j = 0;
		while (j < count - i - 1)
		{
			if (ft_strcmp(sorted[j]->key, sorted[j + 1]->key) > 0)
			{
				temp = sorted[j];
				sorted[j] = sorted[j + 1];
				sorted[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}

void	env_print_sorted(t_env *env)
{
	int			i;
	int			count;
	t_envvar	*curr;
	t_envvar	**sorted;

	count = env_count(env);
	sorted = malloc(sizeof(t_envvar *) * count);
	if (!sorted)
		return ;
	i = 0;
	curr = env->head;
	while (curr)
	{
		sorted[i++] = curr;
		curr = curr->next;
	}
	sort_env_array(sorted, count);
	i = 0;
	while (i < count)
		print_exported_var(sorted[i++]);
	free(sorted);
}
