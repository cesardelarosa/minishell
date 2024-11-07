/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrian <adrian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 22:12:53 by adrian            #+#    #+#             */
/*   Updated: 2024/11/07 22:43:20 by adrian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "libft.h"
#include "minishell.h"

/*
 * Checks if a given string is a valid identifier.
 * A valid identifier starts with an alphabetic character or an underscore,
 * followed by alphanumeric characters or underscores.
 *
 * @param str The string to check.
 * @return 1 if the string is a valid identifier, 0 otherwise.
 */

void	print_exported_variables(void)
{
	extern char	**environ;
	int			i;

	i = 0;
	while (environ[i])
	{
		printf("declare -x %s\n", environ[i]);
		i++;
	}
}

int	is_valid_identifier(const char *str)
{
	int	i;

	i = 1;
	if (!str || !str[0] || (!isalpha(str[0]) && str[0] != '_'))
		return (0);
	while (str[i])
	{
		if (!isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

// Helper function to extract key and value from an argument
int	extract_key_value(char *arg, char **key, char **value)
{
	char	*equal_sign;
	size_t	key_len;

	equal_sign = strchr(arg, '=');
	if (equal_sign)
	{
		key_len = equal_sign - arg;
		*key = (char *)malloc(key_len + 1);
		if (!*key)
			return (-1);
		strncpy(*key, arg, key_len);
		(*key)[key_len] = '\0';
		*value = equal_sign + 1;
		printf("Debug: Key = %s, Value = %s\n", *key, *value);
	}
	else
	{
		*key = strdup(arg);
		if (!*key)
			return (-1);
		*value = NULL;
		printf("Debug: Key = %s, Value is NULL\n", *key);
	}
	return (0);
}

// Helper function to validate the key and set the environment variable
void	validate_and_set_env_var(char *key, char *value)
{
	if (!is_valid_identifier(key))
	{
		printf("export: '%s': not a valid identifier\n", key);
		free(key);
	}
	else
	{
		if (value)
		{
			printf("Debug: Setting environment variable %s=%s\n", key, value);
			setenv(key, value, 1);
		}
		else
		{
			printf("Debug: Setting env variable %s with empty value\n", key);
			setenv(key, "", 1);
		}
		free(key);
	}
}

// Processes each argument passed to export
void	process_export_argument(char *arg)
{
	char	*key;
	char	*value;

	if (extract_key_value(arg, &key, &value) == -1)
		return ;
	validate_and_set_env_var(key, value);
}
