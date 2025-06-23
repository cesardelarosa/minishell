/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <code@cesardelarosa.xyz>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 09:43:38 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/06/23 17:45:40 by cde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "libft.h"
#include "env.h"

t_ctx	init_ctx(char **envp, char *prog_name)
{
	t_ctx	ctx;

	if (ft_strlen(prog_name) > 2)
		ctx.prog_name = ft_strdup(prog_name + 2);
	else
		ctx.prog_name = 0;
	ctx.envp = envp;
	ctx.env = env_init(envp);
	ctx.status = 0;
	if (!ctx.env)
	{
		ft_putstr_fd("minishell: env_init failed\n", 2);
		exit(EXIT_FAILURE);
	}
	return (ctx);
}

void	destroy_ctx(t_ctx *ctx)
{
	if (ctx->prog_name)
		free(ctx->prog_name);
	if (ctx->env)
		env_destroy(ctx->env);
}
