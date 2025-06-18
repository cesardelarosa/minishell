/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin_in_parent.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <code@cesardelarosa.xyz>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 11:02:08 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/06/18 10:48:19 by cesi             ###   ########.fr       */
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

int	destroy_ctx(t_ctx *ctx);

static void	restore_io(int saved_stdin, int saved_stdout)
{
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
}

int	exec_builtin_in_parent(t_pipeline *p, t_builtin_ft builtin_ft)
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
	if (builtin_ft == ft_exit)
	{
		restore_io(saved_stdin, saved_stdout);
		rl_clear_history();
		destroy_ctx(p->ctx);
		error_exit_code(ft_atoi(cmd->argv[1]), NULL, NULL, cmd->p);
	}
	status = builtin_ft(cmd->argv, p->ctx->env);
	restore_io(saved_stdin, saved_stdout);
	return (status);
}
