/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <code@cesardelarosa.xyz>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 21:11:21 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/04/04 17:32:08 by cesi             ###   ########.fr       */
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

static char	*get_var_value(const char *var_name, t_env *env)
{
	t_envvar	*curr;

	curr = env->head;
	while (curr)
	{
		if (ft_strcmp(curr->key, (char *)var_name) == 0)
			return (curr->value);
		curr = curr->next;
	}
	return (NULL);
}

static int	calculate_expanded_length(char *str, t_env *env)
{
	int		len;
	int		i;
	char	*var_name;
	char	*var_value;
	int		start;

	len = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] && (ft_isalnum(str[i + 1]) || str[i
				+ 1] == '_'))
		{
			start = i + 1;
			i++;
			while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
				i++;
			var_name = ft_substr(str, start, i - start);
			if (var_name)
			{
				var_value = get_var_value(var_name, env);
				if (var_value)
					len += ft_strlen(var_value);
				free(var_name);
			}
		}
		else
		{
			len++;
			i++;
		}
	}
	return (len);
}

static void	build_expanded_string(char *result, char *str, t_env *env)
{
	int		i;
	int		j;
	char	*var_name;
	char	*var_value;
	int		start;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] && (ft_isalnum(str[i + 1])
			|| str[i + 1] == '_'))
		{
			start = i + 1;
			i++;
			while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
				i++;
			var_name = ft_substr(str, start, i - start);
			var_value = var_name ? get_var_value(var_name, env) : NULL;
			if (var_value)
			{
				ft_strlcpy(result + j, var_value, ft_strlen(var_value) + 1);
				j += ft_strlen(var_value);
			}
			if (var_name)
				free(var_name);
		}
		else
		{
			result[j++] = str[i++];
		}
	}
	result[j] = '\0';
}

static char	*expand_variables(char *str, t_env *env)
{
	char	*result;
	int		len;

	if (!str)
		return (NULL);
	len = calculate_expanded_length(str, env);
	result = malloc(len + 1);
	if (!result)
		return (NULL);
	build_expanded_string(result, str, env);
	return (result);
}

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
		result = expand_variables(unquoted, env);
		free(unquoted);
		return (result);
	}
	if (len >= 2 && value[0] == '\'' && value[len - 1] == '\'')
		return (ft_substr(value, 1, len - 2));
	return (expand_variables(value, env));
}

static int	process_export_arg(char *arg, t_env *env)
{
	char	*equal_sign;
	char	*key;
	char	*raw_value;
	char	*processed_value;
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
	raw_value = ft_strdup(equal_sign + 1);
	if (!key || !*key || !is_valid_varname(key))
	{
		printf("export: '%s': not a valid identifier\n", key ? key : "");
		result = 1;
	}
	else
	{
		processed_value = handle_quoted_value(raw_value, env);
		if (!processed_value)
			result = 1;
		else
		{
			result = env_set(env, key, processed_value, 1);
			free(processed_value);
		}
	}
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
