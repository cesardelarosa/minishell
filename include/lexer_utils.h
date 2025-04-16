/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <code@cesardelarosa.xyz>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 23:50:14 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/04/03 19:49:30 by cesi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_UTILS_H
# define LEXER_UTILS_H

# include "lexer.h"

int		process_word(char **s, t_list **tokens, int joined);
int		process_pipe(char **s, t_list **tokens);
int		process_redirect_in(char **s, t_list **tokens);
int		process_redirect_out(char **s, t_list **tokens);
int		process_single_quote(char **s, t_list **tokens, int joined);
int		process_double_quote(char **s, t_list **tokens, int joined);

#endif
