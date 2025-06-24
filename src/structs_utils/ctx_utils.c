/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <code@cesardelarosa.xyz>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 09:43:38 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/06/24 08:08:32 by cde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "libft.h"
#include "env.h"

t_ctx	init_ctx(char **envp, char *prog_name)
{
	t_ctx	ctx;
	char	*last_slash;

	last_slash = ft_strrchr(prog_name, '/');
	if (last_slash)
		ctx.prog_name = ft_strdup(last_slash + 1);
	else
		ctx.prog_name = ft_strdup(prog_name);
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
