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
