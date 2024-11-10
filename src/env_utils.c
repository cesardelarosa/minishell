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

// Process special variable '$?'
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

// Process env-vars with name
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

// Process a variable in the string
int	process_variable(char **expanded, char **start)
{
	char	*end;

	end = *start + 1;
	if (*end == '?')
		return (process_exit_status(expanded, start));
	else
		return (process_named_variable(expanded, start, 0));
}
