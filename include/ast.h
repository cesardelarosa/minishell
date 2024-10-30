/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 12:34:01 by cde-la-r          #+#    #+#             */
/*   Updated: 2024/10/30 12:42:52 by cde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

typedef enum e_node_type
{
	COMMAND,
	OPERATOR
}	t_node_type;

typedef enum e_operator_type
{
	PIPE,
	AND,
	OR
}	t_operator_type;

typedef enum e_redirection_type
{
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	HEREDOC
}	t_redirection_type;

typedef struct s_file
{
	t_redirection_type	type;
	int					fd;
	char				*file;
}	t_file;

typedef struct s_command
{
	char		**args;
	char		**envp;
	t_file		input;
	t_file		output;
}	t_command;

typedef struct s_operator
{
	t_operator_type		type;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
}	t_operator;

typedef struct s_ast_node
{
	t_node_type	type;
	union
	{
		t_command	cmd;
		t_operator	op;
	}	u_data;
}	t_ast_node;

void	free_node(t_ast_node *node);

#endif
