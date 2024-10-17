/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrian <adrian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 18:29:51 by cde-la-r          #+#    #+#             */
/*   Updated: 2024/10/17 01:03:54 by cde-la-r         ###   ########.fr       */
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

/*
 * Adds or modifies an environment variable.
 * If the argument is not a valid identifier, an error message is printed.
 * If the argument contains an '=', the variable is set to the specified value.
 * If the argument does not contain an '=', the variable is set to an empty value.
 *
 * @param args An array of strings where the first element is the variable to export.
 */
void	builtin_export(char **args, char **envp)
{
	char	*key;
	char	*value;
	char	*equal_sign;

	if (!args || !args[1])
	{
		for (int i = 0; envp[i]; i++)
			printf("declare -x %s\n", envp[i]);
		return ;
	}
	for (int i = 1; args[i]; i++)
	{
		equal_sign = strchr(args[i], '=');
		if (equal_sign)
		{
			size_t	key_len = equal_sign - args[i];
			key = (char *)malloc(key_len + 1);
			if (!key)
				return ;
			strncpy(key, args[i], key_len);
			key[key_len] = '\0';
			value = equal_sign + 1;
			printf("Debug: Key = %s, Value = %s\n", key, value);
		}
		else
		{
			key = strdup(args[i]);
			value = NULL;
			printf("Debug: Key = %s, Value is NULL\n", key);
		}
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
				printf("Debug: Setting environment variable %s with empty value\n", key);
				setenv(key, "", 1);
			}
			free(key);
		}
	}
}

void	builtin_unset(char **args)
{
	int	i;

	i = 0;
	if (!args || !*args)
		return ;
	while (args[i])
	{
		if (!is_valid_identifier(args[i]))
			printf("unset: '%s': not a valid identifier\n", args[i]);
		else
			unsetenv(args[i]);
		i++;
	}
}

void	builtin_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		printf("%s\n", envp[i]);
		i++;
	}
}
