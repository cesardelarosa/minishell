/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <code@cesardelarosa.xyz>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 11:02:08 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/04/03 00:41:44 by cesi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "common.h"
#include "errors.h"
#include "execution.h"
#include "ft_builtins.h"
#include "pipeline_utils.h"
#include "struct_creation.h"
#include <stdio.h>
#include <readline/history.h>
#include <readline/readline.h>

static void	ft_safe_exit(t_pipeline *p, char **argv, char **envp)
{
	int	exit_status;

	(void)envp;
	exit_status = 0;
	if (argv[1])
		exit_status = ft_atoi(argv[1]);
	pipeline_destroy(p);
	rl_clear_history();
	exit(exit_status);
}

static void	restore_io(int saved_stdin, int saved_stdout)
{
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
}

static int	builtin_in_parent(t_pipeline *p, t_builtin_ft ft, char **envp)
{
	int			saved_stdin;
	int			saved_stdout;
	int			status;
	t_command	*cmd;

	cmd = p->commands->content;
	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	if (handle_redirs(cmd->redirs) < 0)
	{
		restore_io(saved_stdin, saved_stdout);
		error_exit_code(1, "redirection failed", NULL, cmd->p);
	}
	if (ft == ft_exit)
	{
		restore_io(saved_stdin, saved_stdout);
		ft_safe_exit(p, cmd->argv, envp);
	}
	status = is_builtin(cmd->argv[0])(cmd->argv, envp);
	restore_io(saved_stdin, saved_stdout);
	pipeline_destroy(p);
	return (status);
}

int	exec(t_pipeline *p, char **envp)
{
	t_command		*cmd;
	t_builtin_ft	ft_builtin;

	if (!p)
		return (-1);
	if (p->cmd_count == 1)
	{
		cmd = p->commands->content;
		ft_builtin = is_builtin(cmd->argv[0]);
		if (ft_builtin)
			return (builtin_in_parent(p, ft_builtin, envp));
	}
	return (pipeline_execute(p, envp));
}
