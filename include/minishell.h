/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrian <adrian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 22:18:26 by cde-la-r          #+#    #+#             */
/*   Updated: 2024/11/07 22:32:50 by adrian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "ast.h"

# define WELCOME_MSG \
    "\nWelcome to Minishell! by adpedrer & cde-la-r.\nType 'exit' to quit.\n\n"

typedef struct s_copy_data
{
	char	*str;
	int		*i;
	int		*j;
	char	quote_char;
	char	*new_str;
}	t_copy_data;

extern int	g_exit_status;

char		**ft_free_split(char **result);
char		*ft_strjoin_free(char *s1, const char *s2);

void		setup_signal_handlers(void);
char		*read_input(void);
char		**lexer(char *input);
t_ast_node	*parser(char **tokens, char **envp);
void		exec(t_ast_node *root);

char		**parser_comand(char *input, int *i);
void		expand_all_vars(char **args);
int			sup_quotes(char **str, int i, int j);
int			is_quotes(char c);

//env
int			process_variable(char **expanded, char **start);
int			process_exit_status(char **expanded, char **start);
int			return_error(char *error);
char		*ft_strreplace(char *str, char *start, char *end,
				char *replacement);
char		*get_env_var(char *var);
char		*expand_env_vars(char *input);

//builtin
void		process_export_argument(char *arg);
int			is_valid_identifier(const char *str);
void		print_exported_variables(void);

void		print_prompt(void);

#endif
