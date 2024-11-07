/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrian <adrian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 21:20:40 by adrian            #+#    #+#             */
/*   Updated: 2024/11/07 22:31:17 by adrian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"
#include "minishell.h"
#include "builtins.h"
#include <stdlib.h>

int	return_error(char *error)
{
	printf("minishell: %s\n", error);
	return (-1);
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

// Procesa la variable especial '$?'
int	process_exit_status(char **expanded, char **start)
{
	char		*end;
	char		*exit_status_str;
	char		*new_expanded;
	size_t		offset;

	end = *start + 2;
	exit_status_str = ft_itoa(g_exit_status);
	if (!exit_status_str)
		return (return_error("ft_itoa"));
	new_expanded = ft_strreplace(*expanded, *start, end, exit_status_str);
	if (!new_expanded)
	{
		perror("minishell: ft_strreplace");
		free(exit_status_str);
		return (-1);
	}
	offset = (*start - *expanded) + ft_strlen(exit_status_str);
	free(exit_status_str);
	if (*expanded)
		free(*expanded);
	*expanded = new_expanded;
	*start = *expanded + offset;
	return (0);
}

// Procesa variables de entorno con nombre
int	process_named_variable(char **expanded, char **start, size_t offset)
{
	char	*end;
	char	*var;
	char	*value;
	char	*new_expanded;

	end = *start + 1;
	while (ft_isalnum(*end) || *end == '_')
		end++;
	var = ft_substr(*start, 1, end - *start - 1);
	if (!var)
		return (return_error("ft_substr"));
	value = get_env_var(var);
	free(var);
	if (!value)
	{
		*start = end;
		return (0);
	}
	new_expanded = ft_strreplace(*expanded, *start, end, value);
	if (!new_expanded)
		return (return_error("ft_strreplace"));
	offset = (*start - *expanded) + ft_strlen(value);
	*expanded = new_expanded;
	*start = *expanded + offset;
	return (0);
}

// Función auxiliar para procesar una variable en la cadena
int	process_variable(char **expanded, char **start)
{
	char	*end;

	end = *start + 1;
	if (*end == '?')
		return (process_exit_status(expanded, start));
	else
		return (process_named_variable(expanded, start, 0));
}
