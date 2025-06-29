/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <code@cesardelarosa.xyz>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 17:52:04 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/06/23 17:07:37 by cde-la-r         ###   ########.fr       */
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

int	shell_loop(t_ctx *ctx);

int	main(int argc, char **argv, char **envp)
{
	t_ctx	ctx;

	if (argc < 1)
		return (-1);
	ctx = init_ctx(envp, argv[0]);
	env_setup_shell_vars(ctx.env, argv[0]);
	while (shell_loop(&ctx))
		;
	destroy_ctx(&ctx);
	return (ctx.status);
}
