/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <code@cesardelarosa.xyz>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 17:31:31 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/04/10 12:17:51 by cesi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_TOKEN_H
# define PARSE_TOKEN_H

# include "lexer.h"
# include "libft.h"

int	parse_word(t_list **arg_lst, t_token *token, t_ctx *ctx);
int	parse_error(t_token *token);
int	parse_redirection(t_command *cmd, t_list **tokens_ptr, t_token_type op_type,
		t_ctx *ctx);

#endif
