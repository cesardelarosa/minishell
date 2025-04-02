/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <code@cesardelarosa.xyz>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 21:11:21 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/04/01 10:24:40 by cesi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>

int	ft_cd(char **argv, char **envp)
{
	(void)envp;
	if (!argv[1])
	{
		perror("minishell: cd: expected argument");
		return (-1);
	}
	else if (chdir(argv[1]))
	{
		perror("minishell: cd: failed to change directory");
		return (-1);
	}
	return (0);
}
