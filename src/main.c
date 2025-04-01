/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <code@cesardelarosa.xyz>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 17:52:04 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/04/01 11:42:50 by cesi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "libft.h"
#include "struct_creation.h"
#include <stdlib.h>

int	main(int argc, char **argv, char **envp)
{
	int	status;

	(void)argc;
	(void)argv;
	init_signals();
	status = 0;
	while (42)
		status = exec(parser(lexer(read_prompt()), status), envp);
	return (status);
}
