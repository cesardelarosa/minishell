/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrian <adrian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 13:14:30 by cde-la-r          #+#    #+#             */
/*   Updated: 2024/10/04 17:11:01 by adrian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <limits.h>
#include <stdint.h>
#include "libft.h"
#include "minishell.h"
#include "operators.h"

static int	handle_single_redirection(t_ast_node *node, char ***args)
{
	int	check;

	check = 0;
	if (!ft_strcmp(**args, "<") && *(++(*args)))
	{
		check = handle_redirection(&node->u_data.cmd.input, *((*args)++), \
			O_RDONLY);
	}
	else if (!ft_strcmp(**args, ">") && *(++(*args)))
	{
		check = handle_redirection(&node->u_data.cmd.output, *((*args)++), \
			O_WRONLY | O_CREAT | O_TRUNC);
	}
	else if (!ft_strcmp(**args, ">>") && *(++(*args)))
	{
		check = handle_redirection(&node->u_data.cmd.output, *((*args)++), \
			O_WRONLY | O_CREAT | O_APPEND);
	}
	else if (!ft_strcmp(**args, "<<") && *(++(*args)))
		check = handle_heredoc(&node->u_data.cmd.input, *((*args)++));
	return (check);
}

static int	process_redirections(t_ast_node *node, char **args)
{
	int		i;
	int		check;
	char	**new_args;

	new_args = malloc(sizeof(char *) * (ft_strarray_len(args) + 1));
	if (new_args == NULL)
		return (-1);
	i = 0;
	while (*args)
	{
		check = handle_single_redirection(node, &args);
		if (check == -1)
			break ;
		if (check == 0 && *args)
			new_args[i++] = ft_strdup(*args++);
	}
	new_args[i] = NULL;
	ft_free_split(node->u_data.cmd.args);
	node->u_data.cmd.args = new_args;
	return (check);
}

t_ast_node	*create_command(char **tokens, char **envp)
{
	t_ast_node	*node;

	node = malloc(sizeof(t_ast_node));
	if (!node)
		return (NULL);
	node->type = COMMAND;
	node->u_data.cmd.args = tokens;
	node->u_data.cmd.envp = envp;
	ft_init_file(&node->u_data.cmd.input);
	ft_init_file(&node->u_data.cmd.output);
	if (process_redirections(node, node->u_data.cmd.args) == -1)
	{
		free_node(node);
		return (NULL);
	}
	return (node);
}

static t_ast_node	*search_operator(char **tokens, char **envp,
					t_operator_match *ops, size_t ops_len)
{
	int			i;
	size_t		j;
	t_ast_node	*node;

	i = -1;
	while (tokens[++i])
	{
		j = -1;
		while (j++ < ops_len)
		{
			if (ft_strcmp(tokens[i], (char *)ops[j].op_str))
				continue ;
			node = create_operator(ops[j].type);
			if (!node)
				return (NULL);
			node->u_data.op.left = parser(ft_strarray_dup(tokens, \
				0, i - 1), envp);
			node->u_data.op.right = parser(ft_strarray_dup(tokens, \
				i + 1, SIZE_MAX), envp);
			ft_free_split(tokens);
			return (node);
		}
	}
	return (NULL);
}

t_ast_node	*parser(char **tokens, char **envp)
{
	t_ast_node			*node;
	t_operator_match	and_or_ops[2];
	t_operator_match	pipe_ops[1];

	and_or_ops[0].op_str = "&&";
	and_or_ops[0].type = AND;
	and_or_ops[1].op_str = "||";
	and_or_ops[1].type = OR;
	pipe_ops[0].op_str = "|";
	pipe_ops[0].type = PIPE;
	node = search_operator(tokens, envp, and_or_ops, 2);
	if (node != NULL)
		return (node);
	node = search_operator(tokens, envp, pipe_ops, 1);
	if (node != NULL)
		return (node);
	return (create_command(tokens, envp));
}
