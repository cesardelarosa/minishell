/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils_bonus.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <code@cesardelarosa.xyz>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 23:50:14 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/04/12 11:21:17 by cesi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_UTILS_BONUS_H
# define LEXER_UTILS_BONUS_H

# include "lexer.h"

int		process_and(char **s, t_list **tokens);
int		process_or(char **s, t_list **tokens);
int		process_lparen(char **s, t_list **tokens);
int		process_rparen(char **s, t_list **tokens);

#endif
