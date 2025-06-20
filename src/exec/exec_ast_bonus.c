/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_exec_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <code@cesardelarosa.xyz>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 00:06:34 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/06/18 16:52:38 by cde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "structs.h"
#include "ast_utils_bonus.h"
#include <stdlib.h>
#include "core.h"
#include "struct_creation.h"

int			exec(t_pipeline *p);
int			ast_exec(t_ast *ast);

static int	exec_pipeline(char *pipeline_str, t_ctx *ctx)
{
	t_list		*tokens;
	t_pipeline	*pipeline;
	int			status;

	if (!pipeline_str || !*pipeline_str)
		return (0);
	tokens = lexer(pipeline_str);
	pipeline = parser(tokens, ctx);
	ft_lstclear(&tokens, free);
	if (!pipeline)
		return (1);
	status = exec(pipeline);
	pipeline_destroy(pipeline);
	return (status);
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

int	ast_exec(t_ast *ast)
{
	if (!ast)
		return (-1);
	if (ast->type == AST_PIPE)
		return (exec_pipeline(ast->pipeline_str, ast->ctx));
	else if (ast->type == AST_AND)
		return (exec_and(ast));
	else if (ast->type == AST_OR)
		return (exec_or(ast));
	else if (ast->type == AST_GROUP)
		return (exec_group(ast));
	return (-1);
}
