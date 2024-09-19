/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrian <adrian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 17:48:49 by cde-la-r          #+#    #+#             */
/*   Updated: 2024/09/19 17:03:34 by adrian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "minishell.h"

int	main(void)
{
	printf(WELCOME_MSG);
	printf("manuel");
	setup_signal_handlers();
	while (42)
		handle_command(parse_command(read_input()));
	return (0);
}
