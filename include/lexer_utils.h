/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <code@cesardelarosa.xyz>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 23:50:14 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/04/07 23:33:03 by cesi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_UTILS_H
# define LEXER_UTILS_H

# include "lexer.h"

void	process_word(char **s, t_list **tokens, int joined);
int		process_pipe(char **s, t_list **tokens);
int		process_redirect_in(char **s, t_list **tokens);
int		process_redirect_out(char **s, t_list **tokens);
int		process_single_quote(char **s, t_list **tokens, int joined);
int		process_double_quote(char **s, t_list **tokens, int joined);

int		process_and(char **s, t_list **tokens);
int		process_or(char **s, t_list **tokens);
int		process_lparen(char **s, t_list **tokens);
int		process_rparen(char **s, t_list **tokens);

#endif
