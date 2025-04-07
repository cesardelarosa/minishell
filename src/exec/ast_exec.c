/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <code@cesardelarosa.xyz>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 00:06:34 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/04/08 00:06:54 by cde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "structs.h"
#include <stdlib.h>

int			exec(t_pipeline *p);

static int	exec_and(t_ast *ast);
static int	exec_or(t_ast *ast);
static int	exec_group(t_ast *ast);

int	ast_exec(t_ast *ast)
{
	if (!ast)
		return (-1);
	if (ast->type == AST_PIPE)
		return (exec(ast->pipeline));
	else if (ast->type == AST_AND)
		return (exec_and(ast));
	else if (ast->type == AST_OR)
		return (exec_or(ast));
	else if (ast->type == AST_GROUP)
		return (exec_group(ast));
	return (-1);
}

static int	exec_and(t_ast *ast)
{
	int	status;

	if (!ast)
		return (-1);
	status = ast_exec(ast->left);
	if (status == 0)
		status = ast_exec(ast->right);
	return (status);
}

static int	exec_or(t_ast *ast)
{
	int	status;

	if (!ast)
		return (-1);
	status = ast_exec(ast->left);
	if (status != 0)
		status = ast_exec(ast->right);
	return (status);
}

static int	exec_group(t_ast *ast)
{
	if (!ast)
		return (-1);
	return (ast_exec(ast->left));
}
