/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ctx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <code@cesardelarosa.xyz>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 09:12:25 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/04/07 09:12:26 by cde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "libft.h"

t_ctx	init_ctx(char **envp)
{
	t_ctx	ctx;

	ctx.status = 0;
	ctx.envp = envp;
	ctx.env = env_init(envp);
	if (!ctx.env)
	{
		ft_putstr_fd("minishell: env_init failed\n", 2);
		exit(EXIT_FAILURE);
	}
	return (ctx);
}
