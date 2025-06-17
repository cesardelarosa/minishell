/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <code@cesardelarosa.xyz>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 15:38:57 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/06/17 21:11:09 by cde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

typedef struct s_expand_data
{
	char			*expanded;
	int				is_multiple;
	t_token_type	type;
	t_ctx			*ctx;
}	t_expand_data;

char	*expand_value(char *value, t_token_type type, t_ctx *ctx,
			int *is_multiple);

#endif
