/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <code@cesardelarosa.xyz>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 17:52:04 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/04/12 13:19:32 by cesi             ###   ########.fr       */
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
#include "ast_utils_bonus.h"

int		ast_exec(t_ast *ast);
t_ast	*ast_parser(t_list *tokens, t_ctx *ctx);

extern volatile sig_atomic_t	g_sigint_received;

int	main(int argc, char **argv, char **envp)
{
	t_ctx		ctx;
	char		*line;
	t_list		*tokens;
	t_ast		*ast_root;

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
		ast_root = ast_parser(tokens, &ctx);
		ft_lstclear(&tokens, free_token);
		if (!ast_root)
			continue ;
		setup_signals(COMMAND_MODE);
		ctx.status = ast_exec(ast_root);
		ast_destroy(ast_root);
	}
	return (destroy_ctx(&ctx));
}
