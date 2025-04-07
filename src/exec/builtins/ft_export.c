/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <code@cesardelarosa.xyz>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 21:11:21 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/04/07 18:12:39 by cesi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>

static char	*handle_quoted_value(char *value, t_env *env)
{
	int		len;
	char	*result;
	char	*unquoted;

	if (!value)
		return (ft_strdup(""));
	len = ft_strlen(value);
	if ((value[0] == '"' || value[0] == '\'') && value[len - 1] != value[0])
	{
		ft_putstr_fd("export: error: missing closing quote\n", 2);
		return (NULL);
	}
	if (len >= 2 && value[0] == '"' && value[len - 1] == '"')
	{
		unquoted = ft_substr(value, 1, len - 2);
		if (!unquoted)
			return (NULL);
		result = env_expand_variables(unquoted, env);
		free(unquoted);
		return (result);
	}
	if (len >= 2 && value[0] == '\'' && value[len - 1] == '\'')
		return (ft_substr(value, 1, len - 2));
	return (env_expand_variables(value, env));
}

static int	set_env_value(char *key, char *raw_value, t_env *env)
{
	char	*processed_value;
	int		result;

	processed_value = handle_quoted_value(raw_value, env);
	if (!processed_value)
		return (1);
	result = env_set(env, key, processed_value, 1);
	free(processed_value);
	return (result);
}

static int	process_with_equal_sign(char *key, char *raw_value, t_env *env)
{
	int	result;

	if (!key || !*key || !env_is_valid_key(key))
	{
		if (key)
			printf("export: '%s': not a valid identifier\n", key);
		else
			printf("export: '': not a valid identifier\n");
		result = 1;
	}
	else
		result = set_env_value(key, raw_value, env);
	return (result);
}

static int	process_export_arg(char *arg, t_env *env)
{
	char	*equal_sign;
	char	*key;
	char	*raw_value;
	int		result;

	equal_sign = ft_strchr(arg, '=');
	if (!equal_sign)
	{
		if (!env_is_valid_key(arg))
		{
			printf("export: '%s': not a valid identifier\n", arg);
			return (1);
		}
		return (0);
	}
	key = ft_substr(arg, 0, equal_sign - arg);
	raw_value = ft_strdup(equal_sign + 1);
	result = process_with_equal_sign(key, raw_value, env);
	free(key);
	free(raw_value);
	return (result);
}

int	ft_export(char **argv, t_env *env)
{
	int	i;
	int	status;

	if (!argv[1])
	{
		env_print_sorted(env);
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
