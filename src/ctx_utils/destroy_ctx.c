/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_ctx.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <code@cesardelarosa.xyz>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 09:12:19 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/04/08 16:07:17 by cesi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "structs.h"
#include "ast_utils.h"

int	destroy_ctx(t_ctx *ctx)
{
	if (ctx->env)
		env_destroy(ctx->env);
	if (ctx->current_ast)
		ast_destroy(ctx->current_ast);
	return (ctx->status);
}
