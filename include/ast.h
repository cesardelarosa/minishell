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
	OPERATOR
}	t_node_type;

typedef enum e_operator_type
{
	PIPE,
	AND,
	OR
}	t_operator_type;

typedef struct s_file
{
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

t_ast_node	*create_operator(t_operator_type type);
void		free_node(t_ast_node *node);
void		ft_init_file(t_file *file);

#endif
