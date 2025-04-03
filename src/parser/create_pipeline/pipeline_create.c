/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_create.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <code@cesardelarosa.xyz>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 12:16:25 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/04/03 23:32:11 by cesi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct_creation.h"

t_pipeline	*pipeline_create(void)
{
	t_pipeline	*pipeline;

	pipeline = ft_calloc(1, sizeof(t_pipeline));
	return (pipeline);
}
