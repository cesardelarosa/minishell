/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <code@cesardelarosa.xyz>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 12:18:10 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/06/20 12:58:45 by cde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_UTILS_BONUS_H
# define AST_UTILS_BONUS_H

# include "structs.h"

typedef enum e_ast_type
{
	AST_PIPE,
	AST_AND,
	AST_OR,
	AST_GROUP,
	AST_ERROR
}					t_ast_type;

typedef struct s_ast
{
	t_ast_type		type;
	char			*pipeline_str;
	struct s_ast	*left;
	struct s_ast	*right;
	t_ctx			*ctx;
}					t_ast;

t_ast				*ast_create(t_ast_type type, t_ast *left, t_ast *right,
						char *pipeline_str, t_ctx *ctx);
void				ast_destroy(t_ast *ast);

#endif
