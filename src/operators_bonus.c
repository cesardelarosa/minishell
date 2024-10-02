/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operators_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <cde-la-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 15:38:21 by cde-la-r          #+#    #+#             */
/*   Updated: 2024/10/02 15:38:23 by cde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/wait.h>
#include "minishell.h"

void	handle_and(t_ast_node *node)
{
	int	status;

	exec(node->left);
	wait(&status);
	if (WIFEXITED(status) && WEXITSTATUS(status) == 0)
		exec(node->right);
}

void	handle_or(t_ast_node *node)
{
	int	status;

	exec(node->left);
	wait(&status);
	if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
		exec(node->right);
}
