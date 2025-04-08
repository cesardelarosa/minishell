/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <code@cesardelarosa.xyz>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 17:52:04 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/04/08 16:05:22 by cesi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "libft.h"
#include "struct_creation.h"
#include <stdlib.h>
#include "ast_utils.h"

int		ast_exec(t_ast *ast);
t_ast	*ast_parser(t_list *tokens, t_ctx *ctx);

int	main(int argc, char **argv, char **envp)
{
	t_ctx	ctx;
	char	*line;
	t_list	*tokens;

	(void)argc;
	(void)argv;
	ctx = init_ctx(envp);
	while (42)
	{
		line = read_prompt(ctx.status);
		if (!line)
			break ;
		tokens = lexer(line);
		if (!tokens)
			continue ;
		ctx.current_ast = ast_parser(tokens, &ctx);
		ft_lstclear(&tokens, free_token);
		if (!ctx.current_ast)
			continue ;
		ctx.status = ast_exec(ctx.current_ast);
		ast_destroy(ctx.current_ast);
		ctx.current_ast = NULL;
	}
	return (destroy_ctx(&ctx));
}

/*
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
*/
