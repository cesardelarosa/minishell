/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_create.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <code@cesardelarosa.xyz>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 12:16:25 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/04/04 00:38:49 by cesi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct_creation.h"

t_pipeline	*pipeline_create(t_ctx *ctx)
{
	t_pipeline	*pipeline;

	pipeline = ft_calloc(1, sizeof(t_pipeline));
	if (pipeline)
		pipeline->ctx = ctx;
	return (pipeline);
}
