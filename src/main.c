/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <code@cesardelarosa.xyz>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 17:52:04 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/03/31 19:58:09 by cesi             ###   ########.fr       */
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
	while (42)
	{
		line = read_line(envp);
		tokens = lexer(line);
		pipeline = parse_tokens(tokens);
		exit_status = pipeline_execute(pipeline, envp);
	}
	return (exit_status);
}
