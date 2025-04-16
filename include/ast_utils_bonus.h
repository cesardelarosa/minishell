/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <code@cesardelarosa.xyz>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 12:18:10 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/04/16 11:30:26 by cesi             ###   ########.fr       */
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
	AST_GROUP
}					t_ast_type;

typedef struct s_ast
{
	t_ast_type		type;
	t_pipeline		*pipeline;
	struct s_ast	*left;
	struct s_ast	*right;
}	t_ast;

t_ast	*ast_create(int type, t_ast *left, t_ast *right, t_pipeline *pipeline);
void	ast_destroy(t_ast *ast);

#endif
