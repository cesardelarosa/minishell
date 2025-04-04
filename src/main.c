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
#include "env.h"

static t_ctx	init_ctx(char **envp)
{
	t_ctx	ctx;

	ctx.status = 0;
	ctx.envp = envp;
	ctx.env = env_init(envp);
	if (!ctx.env)
	{
		ft_putstr_fd("minishell: env_init failed\n", 2);
		exit(EXIT_FAILURE);
	}
	return (ctx);
}

int	main(int argc, char **argv, char **envp)
{
	t_ctx	ctx;

	(void)argc;
	(void)argv;
	init_signals();
	ctx = init_ctx(envp);
	while (42)
		ctx.status = exec(parser(lexer(read_prompt()), &ctx));
	env_destroy(ctx.env);
	return (ctx.status);
}
