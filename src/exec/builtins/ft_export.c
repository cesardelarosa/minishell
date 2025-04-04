/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <code@cesardelarosa.xyz>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 21:11:21 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/04/04 11:23:25 by cesi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "libft.h"
#include <stdio.h>

static int	is_valid_varname(char *name)
{
	int	i;

	if (!name || !*name)
		return (0);
	if (!(ft_isalpha(name[0]) || name[0] == '_'))
		return (0);
	i = 1;
	while (name[i])
	{
		if (!(ft_isalnum(name[i]) || name[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}

static void	print_exported_var(t_envvar *var)
{
	printf("declare -x %s=\"%s\"\n", var->key, var->value);
}

static void	print_sorted_env(t_env *env)
{
	int			i;
	int			j;
	int			count;
	t_envvar	*curr;
	t_envvar	**sorted;
	t_envvar	*temp;

	count = 0;
	curr = env->head;
	while (curr)
	{
		count++;
		curr = curr->next;
	}
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
	i = 0;
	while (i < count)
		print_exported_var(sorted[i++]);
	free(sorted);
}

static int	process_export_arg(char *arg, t_env *env)
{
	char	*equal_sign;
	char	*key;
	char	*value;
	int		result;

	equal_sign = ft_strchr(arg, '=');
	if (!equal_sign)
	{
		if (!is_valid_varname(arg))
		{
			printf("export: '%s': not a valid identifier\n", arg);
			return (1);
		}
		return (0);
	}
	key = ft_substr(arg, 0, equal_sign - arg);
	value = ft_strdup(equal_sign + 1);
	if (!is_valid_varname(key))
	{
		printf("export: '%s': not a valid identifier\n", arg);
		result = 1;
	}
	else
		result = env_set(env, key, value, 1);
	free(key);
	free(value);
	return (result);
}

int	ft_export(char **argv, t_env *env)
{
	int	i;
	int	status;

	if (!argv[1])
	{
		print_sorted_env(env);
		return (0);
	}
	status = 0;
	i = 1;
	while (argv[i])
	{
		if (process_export_arg(argv[i], env) != 0)
			status = 1;
		i++;
	}
	return (status);
}
