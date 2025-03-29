/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redir.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <code@cesardelarosa.xyz>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 13:02:12 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/03/29 16:28:10 by cesi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HANDLE_REDIR_H
# define HANDLE_REDIR_H

# include "structs.h"

int	handle_redir_in(t_redir *redir);
int	handle_redir_out(t_redir *redir);
int	handle_redir_append(t_redir *redir);
int	handle_heredoc(t_redir *redir);

#endif
