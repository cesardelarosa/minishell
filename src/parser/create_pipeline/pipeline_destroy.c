/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_destroy.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <code@cesardelarosa.xyz>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 12:16:25 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/04/03 23:32:24 by cesi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct_creation.h"

void	pipeline_destroy(t_pipeline *pipeline)
{
	unsigned int	i;

	if (pipeline->pipes)
	{
		i = 0;
		while (i + 1 < pipeline->cmd_count)
		{
			free(pipeline->pipes[i]);
			i++;
		}
		free(pipeline->pipes);
	}
	free(pipeline->pids);
	ft_lstclear(&pipeline->commands, command_destroy);
	free(pipeline);
}
