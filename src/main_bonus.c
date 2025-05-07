/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <code@cesardelarosa.xyz>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 17:52:04 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/05/07 23:22:38 by cesi             ###   ########.fr       */
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
t_ast							*ast_parser(t_list *tokens, t_ctx *ctx);

extern volatile sig_atomic_t	g_sigint_received;

static int	shell_loop_bonus(t_ctx *ctx)
{
	char	*line;
	t_list	*tokens;
	t_ast	*ast_root;

	setup_signals(INTERACTIVE_MODE);
	line = read_prompt(ctx->status);
	if (!line)
		return (EXIT);
	tokens = lexer(line);
	if (!tokens)
		return (CONTINUE);
	ast_root = ast_parser(tokens, ctx);
	ft_lstclear(&tokens, free_token);
	if (!ast_root)
		return (CONTINUE);
	setup_signals(COMMAND_MODE);
	ctx->status = ast_exec(ast_root);
	ast_destroy(ast_root);
	return (CONTINUE);
}

int	main(int argc, char **argv, char **envp)
{
	t_ctx	ctx;

	(void)argc;
	(void)argv;
	ctx = init_ctx(envp);
	while (shell_loop_bonus(&ctx))
		;
	return (destroy_ctx(&ctx));
}
