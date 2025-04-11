/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <code@cesardelarosa.xyz>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 10:16:12 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/04/01 10:47:32 by cesi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "ft_builtins.h"
#include "libft.h"

t_builtin_ft	get_builtin_ft(char *cmd)
{
	size_t					i;
	size_t					n;
	static const t_builtin	builtins[] = {
	{"cd", ft_cd},
	{"echo", ft_echo},
	{"pwd", ft_pwd},
	{"exit", ft_exit},
	{"export", ft_export},
	{"env", ft_env},
	{"unset", ft_unset}
	};

	n = sizeof(builtins) / sizeof(builtins[0]);
	i = 0;
	while (i < n)
	{
		if (ft_strcmp(cmd, builtins[i].name) == 0)
			return (builtins[i].func);
		i++;
	}
	return (NULL);
}
