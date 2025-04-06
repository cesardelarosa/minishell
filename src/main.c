/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <code@cesardelarosa.xyz>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 17:52:04 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/04/04 11:31:26 by cesi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "libft.h"
#include "struct_creation.h"
#include <stdlib.h>

int	main(int argc, char **argv, char **envp)
{
	t_ctx		ctx;
	char		*line;
	t_list		*tokens;
	t_pipeline	*pipeline;

	(void)argc;
	(void)argv;
	ctx = init_ctx(envp);
	init_signals();
	while (42)
	{
		line = read_prompt(ctx.status);
		if (!line)
			break ;
		tokens = lexer(line);
		if (!tokens)
			continue ;
		pipeline = parser(tokens, &ctx);
		if (!pipeline)
			continue ;
		ctx.status = exec(pipeline);
	}
	return (destroy_ctx(&ctx));
}
