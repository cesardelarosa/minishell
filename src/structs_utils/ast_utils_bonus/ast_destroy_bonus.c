/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_destroy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <code@cesardelarosa.xyz>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 12:19:06 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/04/12 12:41:21 by cesi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast_utils_bonus.h"
#include "libft.h"
#include "struct_creation.h"
#include <stdlib.h>

void	ast_destroy(t_ast *ast)
{
	if (!ast)
		return ;
	if (ast->left)
		ast_destroy(ast->left);
	if (ast->right)
		ast_destroy(ast->right);
	free(ast);
}
