/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <code@cesardelarosa.xyz>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 17:15:26 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/04/12 11:13:56 by cesi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "libft.h"

typedef enum e_token_type
{
	TOKEN_PIPE,
	TOKEN_REDIRECT_IN,
	TOKEN_REDIRECT_OUT,
	TOKEN_HEREDOC,
	TOKEN_APPEND,
	TOKEN_WORD,
	TOKEN_SINGLE_QUOTED_STRING,
	TOKEN_DOUBLE_QUOTED_STRING,
	TOKEN_EOF,
	TOKEN_AND,
	TOKEN_OR,
	TOKEN_LPAREN,
	TOKEN_RPAREN,
	TOKEN_ERROR
}					t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	int				joined;
}					t_token;

void				free_token(void *token_ptr);
int					process_token(char **s, t_list **tokens, int joined);
t_list				*lexer(char *input);
t_token				*create_token(t_token_type type, char *value, int joined);

#endif
