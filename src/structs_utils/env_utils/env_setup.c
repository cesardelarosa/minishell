/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_setup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <code@cesardelarosa.xyz>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 22:43:17 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/06/20 22:43:21 by cde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "libft.h"
#include <unistd.h>
#include <limits.h>
#include <stdio.h>

static void	setup_shlvl(t_env *env)
{
	const char	*shlvl_str;
	int			level;
	char		*new_level_str;

	shlvl_str = env_get(env, "SHLVL");
	level = 1;
	if (shlvl_str)
	{
		level = ft_atoi(shlvl_str) + 1;
		if (level <= 1)
			level = 1;
	}
	new_level_str = ft_itoa(level);
	if (!new_level_str)
		return ;
	env_set(env, "SHLVL", new_level_str, 1);
	free(new_level_str);
}

static void	setup_pwd(t_env *env)
{
	char	cwd_path[PATH_MAX];

	if (getcwd(cwd_path, sizeof(cwd_path)) != NULL)
		env_set(env, "PWD", cwd_path, 1);
	else
		perror("minishell: error al inicializar PWD");
}

void	env_setup_shell_vars(t_env *env, char *prog_name)
{
	if (!env)
		return ;
	setup_pwd(env);
	setup_shlvl(env);
	env_set(env, "_", prog_name, 1);
	env_unset(env, "OLDPWD");
}
