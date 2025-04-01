/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <code@cesardelarosa.xyz>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 21:11:43 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/03/31 21:17:32 by cde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>

int	ft_pwd(char **argv, char **envp)
{
	char	cwd[1024];

	(void)argv;
	(void)envp;
	if (!getcwd(cwd, sizeof(cwd)))
	{
		perror("minishell: pwd: failed to get current directory");
		return (-1);
	}
	printf("%s\n", cwd);
	return (0);
}
