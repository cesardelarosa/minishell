/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <code@cesardelarosa.xyz>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 17:24:58 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/03/29 17:25:01 by cde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "structs.h"
# include "libft.h"
# include "lexer.h"

t_pipeline	*parse_tokens(t_list *tokens);
void		free_tokens(t_list *tokens);

#endif
