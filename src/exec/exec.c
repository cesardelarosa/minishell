/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <code@cesardelarosa.xyz>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 11:02:08 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/04/10 11:37:26 by cesi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "common.h"
#include "errors.h"
#include "execution.h"
#include "ft_builtins.h"
#include "struct_creation.h"
#include <stdio.h>
#include <readline/history.h>
#include <readline/readline.h>

int	exec_builtin_in_parent(t_pipeline *p, t_builtin_ft ft);

int	exec(t_pipeline *p)
{
	t_builtin_ft	ft_builtin;
	t_command		*cmd;

	if (!p)
		return (-1);
	if (p->cmd_count == 1)
	{
		cmd = p->commands->content;
		ft_builtin = get_builtin_ft(cmd->argv[0]);
		if (ft_builtin)
			return (exec_builtin_in_parent(p, ft_builtin));
	}
	return (pipeline_execute(p));
}
