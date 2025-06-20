/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <code@cesardelarosa.xyz>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 21:11:21 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/06/20 22:50:22 by cde-la-r         ###   ########.fr       */
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

void	error_cd(char *bad_path)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(bad_path, 2);
	ft_putendl_fd(": ", 2);
	ft_putendl_fd(strerror(errno), 2);
}

int	ft_cd(char **argv, t_env *env)
{
	char	*oldpwd;
	char	new_cwd[4096];

	if (!argv[1])
		return (ft_putstr_fd("minishell: cd: path argument required\n", 2), 1);
	if (argv[2])
		return (ft_putstr_fd("minishell: cd: too many arguments\n", 2), 1);
	oldpwd = env_get(env, "PWD");
	if (chdir(argv[1]) != 0)
	{
		error_cd(argv[1]);
		return (1);
	}
	if (oldpwd)
		env_set(env, "OLDPWD", oldpwd, 1);
	if (getcwd(new_cwd, sizeof(new_cwd)) != NULL)
		env_set(env, "PWD", new_cwd, 1);
	else
	{
		ft_putstr_fd("minishell: cd: error retrieving current directory\n", 2);
		return (1);
	}
	return (0);
}
