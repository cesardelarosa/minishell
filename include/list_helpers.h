/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_helpers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <code@cesardelarosa.xyz>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 17:32:40 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/04/07 17:40:29 by cesi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_HELPERS_H
# define LIST_HELPERS_H

# include "libft.h"

void	add_arg_to_list(t_list **arg_lst, char *arg);
char	*get_last_arg(t_list *arg_lst);
void	update_last_arg(t_list *arg_lst, char *new_content);
char	*expand_value(char *value, t_token_type type, t_ctx *ctx,
			int *is_multiple);

#endif
