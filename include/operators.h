/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operators.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <cde-la-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 16:42:48 by cde-la-r          #+#    #+#             */
/*   Updated: 2024/10/30 20:22:45 by cde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPERATORS_H
# define OPERATORS_H

int		handle_redir_in(t_file *input, const char *filename);
int		handle_redir_out(t_file *output, const char *filename, int type);
int		handle_heredoc(t_file *input, const char *delimiter);
void	handle_pipe(t_operator op);
void	handle_and(t_operator op);
void	handle_or(t_operator op);

#endif
