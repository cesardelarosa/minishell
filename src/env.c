/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 16:35:10 by cde-la-r          #+#    #+#             */
/*   Updated: 2024/10/01 16:58:36 by cde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"
#include "minishell.h"
#include "builtins.h"

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
