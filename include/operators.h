/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operators.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <cde-la-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 10:08:34 by cde-la-r          #+#    #+#             */
/*   Updated: 2024/10/03 10:08:47 by cde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPERATORS_H
# define OPERATORS_H

# include "ast.h"

void	handle_pipe(t_ast_node *node);
void	handle_redirection_in(t_ast_node *node);
void	handle_redirection_out(t_ast_node *node);
void	handle_redirection_append(t_ast_node *node);
void	handle_heredoc(t_ast_node *node);

#endif
