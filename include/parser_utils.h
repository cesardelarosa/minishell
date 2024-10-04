/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 13:39:56 by cde-la-r          #+#    #+#             */
/*   Updated: 2024/09/19 18:11:01 by cde-la-r         ###   ########.fr       */
/*   Created: 2024/10/01 14:51:57 by cde-la-r          #+#    #+#             */
/*   Updated: 2024/10/01 14:51:59 by cde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_UTILS_H
#define PARSER_UTILS_H

#include "ast.h"

int is_operator(const char *token);
t_node_type get_operator_type(const char *token);
int find_highest_operator(char **tokens, int start, int end);
char **dup_args_range(char **tokens, int start, int end);

#endif
