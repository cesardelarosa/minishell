/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <code@cesardelarosa.xyz>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 17:52:04 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/03/29 18:41:16 by cesi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "core.h"
#include "libft.h"
#include "struct_creation.h"
#include <stdlib.h>

int	main(int argc, char **argv, char **envp)
{
	char		*line;
	t_list		*tokens;
	t_pipeline	*pipeline;
	int			exit_status;

	(void)argc;
	(void)argv;
	init_signals();
	while (1)
	{
		line = read_line(envp);
		if (!line)
			break ;
		tokens = lexer(line);
		free(line);
		if (!tokens)
			continue ;
		pipeline = parse_tokens(tokens);
		free_tokens(tokens);
		if (!pipeline)
			continue ;
		exit_status = pipeline_execute(pipeline, envp);
		pipeline_destroy(pipeline);
	}
	return (exit_status);
}
