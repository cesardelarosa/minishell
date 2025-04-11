/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_ctx.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <code@cesardelarosa.xyz>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 09:12:19 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/04/07 09:12:21 by cde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "env.h"

int	destroy_ctx(t_ctx *ctx)
{
	if (ctx->env)
		env_destroy(ctx->env);
	return (ctx->status);
}
