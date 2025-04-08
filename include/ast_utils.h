/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <code@cesardelarosa.xyz>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 12:18:10 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/04/08 12:18:12 by cde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_UTILS_H
# define AST_UTILS_H

# include "structs.h"

t_ast	*ast_create(int type, t_ast *left, t_ast *right, t_pipeline *pipeline);
void	ast_destroy(t_ast *ast);

#endif
