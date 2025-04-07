/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_handlers.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <code@cesardelarosa.xyz>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 17:31:31 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/04/07 17:38:33 by cesi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_HANDLERS_H
# define TOKEN_HANDLERS_H

# include "lexer.h"
# include "libft.h"

int	process_word_token(t_list **arg_lst, t_token *token, t_ctx *ctx);
int	handle_joined_token(t_list *arg_lst, char *expanded, t_token_type type,
		int is_multiple);
int	handle_joined_multiple(t_list *arg_lst, char *expanded, char *last_arg);
int	handle_normal_multiple(t_list **arg_lst, char *expanded);
int	handle_normal_token(t_list **arg_lst, char *expanded, t_token_type type,
		int is_multiple);
int	handle_error_token(t_token *token);
int	handle_redirection(t_command *cmd, t_list **tokens_ptr,
		t_token_type op_type, t_ctx *ctx);

#endif
