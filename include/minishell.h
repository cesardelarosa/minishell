/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrian <adrian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 22:18:26 by cde-la-r          #+#    #+#             */
/*   Updated: 2024/10/01 21:58:36 by adrian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "ast.h"
#include <sys/types.h>
#include <sys/wait.h>

extern int g_exit_err_val;


# define WELCOME_MSG \
    "\nWelcome to Minishell! by adpedrer & cde-la-r.\nType 'exit' to quit.\n\n"

char		**ft_free_split(char **result);
char		*ft_strjoin_free(char *s1, const char *s2);

void		setup_signal_handlers(void);
char		*read_input(void);
char		**lexer(char *input);
t_ast_node	*parser(char **tokens);
void		exec(t_ast_node *root);

void		expand_all_vars(char **args);

#endif
