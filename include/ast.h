/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 12:34:01 by cde-la-r          #+#    #+#             */
/*   Updated: 2024/10/01 14:35:52 by cde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

typedef enum e_node_type
{
	COMMAND,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	HEREDOC,
	AND,
	OR
}	t_node_type;

typedef struct s_ast_node
{
	t_node_type			type;
	char				**args;
	char				**envp;
	char				*delimiter;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
}	t_ast_node;

t_ast_node	*create_node(t_node_type type, char **args, char **envp);
void		free_node(t_ast_node *node);
void		print_node(t_ast_node *root);
void		add_node(t_ast_node **root, t_ast_node *new_node);

#endif
