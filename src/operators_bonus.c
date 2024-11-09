/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operators_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <cde-la-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 10:13:31 by cde-la-r          #+#    #+#             */
/*   Updated: 2024/10/03 10:13:36 by cde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ast.h"

void	handle_and(t_operator op)
{
	exec(op.left);
	if (g_exit_status == 0)
		exec(op.right);
}

void	handle_or(t_operator op)
{
	exec(op.left);
	if (g_exit_status != 0)
		exec(op.right);
}
