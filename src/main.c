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
#include "ctx.h"

int	main(int argc, char **argv, char **envp)
{
	t_ctx	ctx;

	(void)argc;
	(void)argv;
	init_signals();
	ctx = init_ctx(envp);
	while (42)
		ctx.status = exec(parser(lexer(read_prompt()), &ctx));
	return (destroy_ctx(&ctx));
}
