/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrian <adrian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 13:14:30 by cde-la-r          #+#    #+#             */
/*   Updated: 2024/10/30 13:20:29 by cde-la-r         ###   ########.fr       */
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

static int	process_redirections(t_ast_node *node, char **args)
{
	int		i;
	int		j;
	int		check;
	char	**new_args;

	check = 0;
	new_args = malloc(sizeof(char *) * (ft_strarray_len(args) + 1));
	if (new_args == NULL)
		return (-1);
	j = 0;
	i = -1;
	while (args[++i] && check != -1)
	{
		if (!ft_strcmp(args[i], "<") && args[i + 1])
			check = handle_redir_in(&node->u_data.cmd.input, args[++i]);
		else if (!ft_strcmp(args[i], ">") && args[i + 1])
			check = handle_redir_out(&node->u_data.cmd.output, args[++i], O_TRUNC);
		else if (!ft_strcmp(args[i], ">>") && args[i + 1])
			check = handle_redir_out(&node->u_data.cmd.output, args[++i], O_APPEND);
		else if (!ft_strcmp(args[i], "<<") && args[i + 1])
			check = handle_heredoc(&node->u_data.cmd.input, args[++i]);
		else
			new_args[j++] = ft_strdup(args[i]);
	}
	new_args[j] = NULL;
	ft_free_split(node->u_data.cmd.args);
	node->u_data.cmd.args = new_args;
	return (check);
}

t_ast_node	*create_command(char **tokens, char **envp)
{
	t_ast_node	*node;
	int			check;

	node = malloc(sizeof(t_ast_node));
	if (!node)
		return (NULL);
	node->type = COMMAND;
	node->u_data.cmd.args = tokens;
	node->u_data.cmd.envp = envp;
	ft_init_file(&node->u_data.cmd.input);
	ft_init_file(&node->u_data.cmd.output);
	check = process_redirections(node, node->u_data.cmd.args);
	if (check == -1)
	{
		free_node(node);
		return (NULL);
	}
	return (node);
}

t_ast_node	*search_and_or(char **tokens, char **envp)
{
	int				i;
	t_ast_node		*node;
	t_operator_type	type;

	type = -1;
	i = -1;
	while (tokens[++i])
	{
		if (ft_strncmp(tokens[i], "&&", 3) == 0)
			type = AND;
		else if (ft_strncmp(tokens[i], "||", 3) == 0)
			type = OR;
		else
			continue ;
		node = create_operator(type);
		if (!node)
			return (NULL);
		node->u_data.op.left = parser(ft_strarray_dup(tokens, 0, i - 1), envp);
		node->u_data.op.right = parser(ft_strarray_dup(tokens, i + 1, SIZE_MAX), envp);
		ft_free_split(tokens);
		return (node);
	}
	return (NULL);
}

t_ast_node	*search_pipe(char **tokens, char **envp)
{
	int			i;
	t_ast_node	*node;

	i = -1;
	while (tokens[++i])
	{
		if (ft_strncmp(tokens[i], "|", 2) != 0)
			continue ;
		node = create_operator(PIPE);
		if (!node)
			return (NULL);
		node->u_data.op.left = parser(ft_strarray_dup(tokens, 0, i - 1), envp);
		node->u_data.op.right = parser(ft_strarray_dup(tokens, i + 1, SIZE_MAX), envp);
		ft_free_split(tokens);
		return (node);
	}
	return (NULL);
}

t_ast_node	*parser(char **tokens, char **envp)
{
	t_ast_node	*node;

	node = search_and_or(tokens, envp);
	if (node != NULL)
		return (node);
	node = search_pipe(tokens, envp);
	if (node != NULL)
		return (node);
	return (create_command(tokens, envp));
}
