/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrian <adrian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 18:29:51 by cde-la-r          #+#    #+#             */
/*   Updated: 2024/11/07 22:41:57 by adrian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "libft.h"
#include "minishell.h"

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
			unsetenv(args[i]);
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
