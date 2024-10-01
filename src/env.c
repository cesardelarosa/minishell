/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 16:35:10 by cde-la-r          #+#    #+#             */
/*   Updated: 2024/10/01 17:45:54 by cde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"
#include "minishell.h"
#include "builtins.h"

/*
** Retrieves the value of the specified environment variable.
** If the variable is not found, it prints an error message.
**
** @param var: The name of the environment variable to retrieve.
** @return: The value of the variable, or NULL if not found.
*/
char	*get_env_var(char *var)
{
	char	*value;

	value = getenv(var);
	if (value == NULL)
	{
		printf("minishell: getenv: %s: variable not found\n", var);
		return (NULL);
	}
	return (value);
}

/*
** Replaces a substring in the original string with a new substring.
** Allocates memory for the new string and returns it.
**
** @param str: The original string in which to replace the substring.
** @param start: A pointer to the start of the substring to replace.
** @param end: A pointer to the end of the substring to replace.
** @param replacement: The substring to insert in place of the original.
** @return: The newly allocated string with the replacement, or exits on failure.
*/
char	*ft_strreplace(char *str, char *start, char *end, char *replacement)
{
	char	*new_str;
	size_t	len;
	size_t	rep_len;
	size_t	new_len;

	len = ft_strlen(str);
	rep_len = ft_strlen(replacement);
	new_len = len - (end - start) + rep_len;
	new_str = (char *)malloc(new_len + 1);
	if (new_str == NULL)
	{
		perror("minishell: malloc");
		exit(EXIT_FAILURE);
	}
	ft_memcpy(new_str, str, start - str);
	ft_memcpy(new_str + (start - str), replacement, rep_len);
	ft_memcpy(new_str + (start - str) + rep_len, end, len - (end - str));
	new_str[new_len] = '\0';
	free(str);
	return (new_str);
}

/*
** Expands environment variables in the input string.
** For each variable found, it replaces it with its value.
**
** @param input: The input string that may contain environment variables.
** @return: A new string with the variables expanded, or NULL on failure.
*/
char	*expand_env_vars(char *input)
{
	char	*expanded;
	char	*start;
	char	*end;
	char	*var;
	char	*value;

	expanded = ft_strdup(input);
	if (!expanded)
	{
		perror("minishell: ft_strdup");
		return (NULL);
	}
	start = expanded;
	while (1)
	{
		start = ft_strchr(start, '$');
		if (!start)
			break ;
		end = start + 1;
		while (ft_isalnum(*end) || *end == '_')
			end++;
		var = ft_substr(start, 1, end - start - 1);
		if (!var)
		{
			perror("minishell: ft_substr");
			free(expanded);
			return (NULL);
		}
		value = get_env_var(var);
		free(var);
		if (!value)
		{
			start = end;
			continue ;
		}
		expanded = ft_strreplace(expanded, start, end, value);
		if (!expanded)
		{
			perror("minishell: ft_strreplace");
			return (NULL);
		}
		start += ft_strlen(value);
	}
	return (expanded);
}

/*
** Expands all environment variables in the given array of arguments.
** Each argument in args is replaced with its expanded version.
**
** @param args: The array of strings (arguments) to expand.
*/
void	expand_all_vars(char **args)
{
	int		i;
	char	*expanded;

	i = 0;
	while (args[i])
	{
		expanded = expand_env_vars(args[i]);
		free(args[i]);
		args[i] = expanded;
		i++;
	}
}
