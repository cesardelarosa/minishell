/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <code@cesardelarosa.xyz>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 17:52:04 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/04/11 17:29:39 by cesi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "libft.h"
#include "signals.h"
#include "struct_creation.h"
#include <stdio.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdlib.h>
#include <unistd.h>

extern volatile sig_atomic_t	g_sigint_received;

int	main(int argc, char **argv, char **envp)
{
	t_ctx		ctx;
	char		*line;
	t_list		*tokens;
	t_pipeline	*pipeline;

	(void)argc;
	(void)argv;
	ctx = init_ctx(envp);
	while (42)
	{
		setup_signals(INTERACTIVE_MODE);
		line = read_prompt(ctx.status);
		if (!line)
			break ;
		tokens = lexer(line);
		if (!tokens)
			continue ;
		pipeline = parser(tokens, &ctx);
		if (!pipeline)
			continue ;
		setup_signals(COMMAND_MODE);
		ctx.status = exec(pipeline);
	}
	return (destroy_ctx(&ctx));
}
