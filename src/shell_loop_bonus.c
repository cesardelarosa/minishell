/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <code@cesardelarosa.xyz>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 17:52:04 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/06/18 16:57:09 by cde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast_utils_bonus.h"
#include "core.h"
#include "libft.h"
#include "signals.h"
#include "struct_creation.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/history.h>
#include <readline/readline.h>

#define EXIT 0
#define CONTINUE 1

int								ast_exec(t_ast *ast);
t_ast							*ast_parser(char **s, t_ctx *ctx);

extern volatile sig_atomic_t	g_sigint_received;

int	shell_loop(t_ctx *ctx)
{
	char	*line;
	t_ast	*ast_root;

	setup_signals(INTERACTIVE_MODE);
	line = read_prompt(ctx->status);
	if (!line)
		return (EXIT);
	ast_root = ast_parser(&line, ctx);
	if (!ast_root)
		ctx->status = 2;
	else
	{
		setup_signals(COMMAND_MODE);
		ctx->status = ast_exec(ast_root);
		ast_destroy(ast_root);
	}
	free(line);
	return (CONTINUE);
}
