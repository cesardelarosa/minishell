/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrian <adrian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 18:29:51 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/03/30 13:14:23 by cesi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "libft.h"

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
		printf("declare -x %s\n", environ[i++]);
}

int	is_valid_identifier(const char *str)
{
	int	i;

	if (!str || !str[0] || (!ft_isalpha(str[0]) && str[0] != '_'))
		return (0);
	i = 0;
	while (str[++i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
	}
	return (1);
}

// Helper function to extract key and value from an argument
int	extract_key_value(char *arg, char **key, char **value)
{
	char	*equal_sign;
	size_t	key_len;

	equal_sign = ft_strchr(arg, '=');
	if (equal_sign)
	{
		key_len = equal_sign - arg;
		*value = equal_sign + 1;
	}
	else
	{
		key_len = ft_strlen(arg);
		*value = NULL;
	}
	*key = (char *)malloc(key_len + 1);
	if (!*key)
	{
		perror("minishell: memory allocation");
		return (-1);
	}
	ft_strlcpy(*key, arg, key_len + 1);
	return (0);
}

// Helper function to validate the key and set the environment variable
void	validate_and_set_env_var(char *key, char *value)
{
	if (!is_valid_identifier(key))
		printf("export: '%s': not a valid identifier\n", key);
	else if (setenv(key, value, 1) != 0)
		perror("minishell: error setting enviroment variable");
	free(key);
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

// The main builtin_export function
void	builtin_export(char **args)
{
	int	i;

	if (!args || !args[1])
	{
		print_exported_variables();
		return ;
	}
	i = 1;
	while (args[i])
	{
		process_export_argument(args[i]);
		i++;
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
			unsetenv(args[i]);	// El subject no deja usar unsetenv
		i++;
	}
}

void	builtin_env(void)
{
	extern char	**environ;
	int			i;

	i = 0;
	while (environ[i])
	{
		printf("%s\n", environ[i]);
		i++;
	}
}
