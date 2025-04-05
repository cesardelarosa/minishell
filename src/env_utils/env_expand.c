/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesi <cesi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 17:42:00 by cesi              #+#    #+#             */
/*   Updated: 2025/04/04 17:42:00 by cesi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "libft.h"
#include <stdlib.h>

static char	*extract_var_name(char *str, int *i)
{
	int		start;
	char	*var_name;

	start = *i + 1;
	(*i)++;
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		(*i)++;
	var_name = ft_substr(str, start, *i - start);
	return (var_name);
}

static int	get_var_length(char *var_name, t_env *env)
{
	char	*var_value;
	int		length;

	length = 0;
	if (var_name)
	{
		var_value = env_get(env, var_name);
		if (var_value)
			length = ft_strlen(var_value);
		free(var_name);
	}
	return (length);
}

static int	calculate_expanded_length(char *str, t_env *env)
{
	int		len;
	int		i;
	char	*var_name;

	len = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1]
			&& (ft_isalnum(str[i + 1]) || str[i + 1] == '_'))
		{
			var_name = extract_var_name(str, &i);
			len += get_var_length(var_name, env);
		}
		else
		{
			len++;
			i++;
		}
	}
	return (len);
}

static int	process_variable(char *result, int j, char *var_name, t_env *env)
{
	char	*var_value;

	var_value = NULL;
	if (var_name)
		var_value = env_get(env, var_name);
	if (var_value)
		j += ft_strlcpy(result + j, var_value, ft_strlen(var_value) + 1);
	if (var_name)
		free(var_name);
	return (j);
}

static void	build_expanded_string(char *result, char *str, t_env *env)
{
	int		i;
	int		j;
	char	*var_name;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1]
			&& (ft_isalnum(str[i + 1]) || str[i + 1] == '_'))
		{
			var_name = extract_var_name(str, &i);
			j = process_variable(result, j, var_name, env);
		}
		else
			result[j++] = str[i++];
	}
	result[j] = '\0';
}

char	*env_expand_variables(char *str, t_env *env)
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
