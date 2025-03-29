/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <code@cesardelarosa.xyz>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 16:39:31 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/03/29 16:39:33 by cde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct_creation.h"
#include "execution.h"
#include "libft.h"
#include <stdlib.h>

int	main(int argc, char **argv, char **envp)
{
	char		*line;
	char		**cmds;
	t_pipeline	*pipeline;
	int			exit_status;
	int			i;

	(void)argc;
	(void)argv;
	while (1)
	{
		ft_putstr_fd("minishell$ ", 1);
		line = get_next_line(0);
		if (!line)
			break ;
		if (!*line || ft_strlen(line) <= 1)
		{
			free(line);
			continue ;
		}
		pipeline = pipeline_create();
		if (!pipeline)
		{
			ft_putstr_fd("Error: pipeline_create failed\n", 2);
			free(line);
			continue ;
		}
		cmds = ft_split(line, '|');
		free(line);
		if (!cmds)
		{
			ft_putstr_fd("Error: ft_split failed\n", 2);
			pipeline_destroy(pipeline);
			continue ;
		}
		i = 0;
		while (cmds[i])
		{
			if (!pipeline_add_command(pipeline, command_create(cmds[i])))
				ft_putstr_fd("Error: pipeline_add_command failed\n", 2);
			i++;
		}
		ft_free_split(cmds);
		if (pipeline->cmd_count > 0)
			exit_status = pipeline_execute(pipeline, envp);
		else
			exit_status = 0;
		pipeline_destroy(pipeline);
	}
	return (exit_status);
}
