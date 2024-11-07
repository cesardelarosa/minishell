/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrian <adrian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 16:35:10 by cde-la-r          #+#    #+#             */
/*   Updated: 2024/11/07 21:23:23 by adrian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"
#include "minishell.h"
#include "builtins.h"
#include <stdlib.h>

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

// Función para expandir variables de entorno en una cadena
char	*expand_env_vars(char *input)
{
	char	*expanded;
	char	*start;

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
		if (process_variable(&expanded, &start) != 0)
		{
			free(expanded);
			return (NULL);
		}
	}
	return (expanded);
}

// Función auxiliar para procesar cada argumento
int	process_arg(char **arg, size_t len, char *temp, char *expanded)
{
	len = ft_strlen(*arg);
	if (len >= 2 && (*arg)[0] == '\'' && (*arg)[len - 1] == '\'')
	{
		temp = ft_substr(*arg, 1, len - 2);
		if (!temp)
		{
			g_exit_status = 1;
			return (return_error("malloc"));
		}
		free(*arg);
		*arg = temp;
	}
	else
	{
		expanded = expand_env_vars(*arg);
		if (!expanded)
		{
			g_exit_status = 1;
			return (return_error("expansion error"));
		}
		free(*arg);
		*arg = expanded;
	}
	return (0);
}

// Expande todas las variables de entorno en el array de argumentos
void	expand_all_vars(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if (process_arg(&args[i], 0, NULL, NULL) != 0)
			return ;
		i++;
	}
}
