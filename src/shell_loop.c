/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <code@cesardelarosa.xyz>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 17:52:04 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/06/18 15:47:17 by cesi             ###   ########.fr       */
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

extern volatile sig_atomic_t	g_sigint_received;

int	shell_loop(t_ctx *ctx)
{
	char		*line;
	t_list		*tokens;
	t_pipeline	*pipeline;

	setup_signals(INTERACTIVE_MODE);
	line = read_prompt(ctx->status);
	if (!line)
		return (EXIT);
	tokens = lexer(line);
	free(line);
	if (!tokens)
		return (CONTINUE);
	pipeline = parser(tokens, ctx);
	ft_lstclear(&tokens, free_token);
	if (!pipeline)
		return (CONTINUE);
	setup_signals(COMMAND_MODE);
	ctx->status = exec(pipeline);
	pipeline_destroy(pipeline);
	return (CONTINUE);
}
