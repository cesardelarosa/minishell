/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <code@cesardelarosa.xyz>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 11:02:08 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/04/01 11:04:54 by cesi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "builtin.h"
#include "struct_creation.h"
#include "libft.h"

int	exec(t_pipeline *p, char **envp)
{
	t_command		*cmd;
	t_builtin_ft	ft_builtin;
	int				status;

	if (!p)
		return (-1);
	if (p->cmd_count == 1)
	{
		cmd = p->commands->content;
		ft_builtin = is_builtin(cmd->argv[0]);
		if (ft_builtin)
		{
			status = ft_builtin(cmd->argv, envp);
			pipeline_destroy(p);
			return (status);
		}
	}
	return (pipeline_execute(p, envp));
}
