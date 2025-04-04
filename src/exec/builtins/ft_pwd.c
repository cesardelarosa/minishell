/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <code@cesardelarosa.xyz>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 21:11:43 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/04/04 11:10:43 by cde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include "env.h"

int	ft_pwd(char **argv, t_env *env)
{
	char	cwd[1024];

	(void)argv;
	(void)env;
	if (!getcwd(cwd, sizeof(cwd)))
	{
		perror("minishell: pwd: failed to get current directory");
		return (-1);
	}
	printf("%s\n", cwd);
	return (0);
}
