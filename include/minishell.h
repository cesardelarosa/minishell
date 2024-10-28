/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <cde-la-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 22:18:26 by cde-la-r          #+#    #+#             */
/*   Updated: 2024/10/12 12:06:56 by cde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "ast.h"

# define WELCOME_MSG \
    "\nWelcome to Minishell by adpedrer & cde-la-r!\nType 'exit' to quit.\n\n"

extern int	g_exit_status;

void		setup_signal_handlers(void);
void		print_prompt(void);
char		*read_input(void);
char		**lexer(char *input);
t_ast_node	*parser(char **tokens, char **envp);
void		expand_all_vars(char **args);
void		exec(t_ast_node *root);

#endif
