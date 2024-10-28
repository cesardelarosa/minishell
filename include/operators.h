/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operators.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <cde-la-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 16:42:48 by cde-la-r          #+#    #+#             */
/*   Updated: 2024/10/28 16:42:49 by cde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPERATORS_H
# define OPERATORS_H

void	handle_redir_in(t_file *input, const char *filename);
void	handle_redir_out(t_file *output, const char *filename, int type);
void	handle_heredoc(t_file *input, const char *delimiter);

#endif
