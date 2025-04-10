/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <code@cesardelarosa.xyz>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 21:11:21 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/04/04 11:12:18 by cde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "env.h"
#include "errors.h"
#include "structs.h"

int	ft_cd(char **argv, t_env *env)
{
	char	cwd[4096];
	char	new_cwd[4096];

	if (!argv[1])
		return (ft_putstr_fd("minishell: cd: path argument required\n", 2), 1);
	if (argv[1] && argv[2])
		return (ft_putstr_fd("minishell: cd: too many arguments\n", 2), 1);
	if (getcwd(cwd, sizeof(cwd)) == NULL)
		return (1);
	if (chdir(argv[1]) != 0)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(argv[1], 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(strerror(errno), 2);
		return (1);
	}
	if (getcwd(new_cwd, sizeof(new_cwd)) == NULL)
		return (1);
	env_set(env, "OLDPWD", cwd, 1);
	env_set(env, "PWD", new_cwd, 1);
	return (0);
}
