/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <code@cesardelarosa.xyz>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 17:52:04 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/06/25 00:59:20 by cde-la-r         ###   ########.fr       */
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

#define EXIT 0
#define CONTINUE 1

int	shell_loop(t_ctx *ctx)
{
	char		*line;
	t_list		*tokens;
	t_pipeline	*pipeline;

	g_sigint_received = 0;
	setup_signals(INTERACTIVE_MODE);
	line = read_prompt(ctx);
	if (!line)
		return (EXIT);
	tokens = lexer(line);
	free(line);
	if (!tokens)
		return (CONTINUE);
	pipeline = parser(tokens, ctx);
	ft_lstclear(&tokens, free_token);
	if (g_sigint_received)
		return (ctx->status = 130, CONTINUE);
	if (!pipeline)
		return (ctx->status = 2, CONTINUE);
	setup_signals(COMMAND_MODE);
	ctx->status = exec(pipeline) % 256;
	pipeline_destroy(pipeline);
	return (CONTINUE);
}
