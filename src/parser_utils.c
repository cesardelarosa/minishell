/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 14:51:46 by cde-la-r          #+#    #+#             */
/*   Updated: 2024/10/01 17:49:18 by cde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

/*
** Checks if the provided token is a recognized operator in the shell.
**
** @param token: The token to check.
** @return: 1 if the token is an operator, 0 otherwise.
*/
int	is_operator(const char *token)
{
	return (!ft_strncmp(token, "|", 2)
		|| !ft_strncmp(token, ">", 2)
		|| !ft_strncmp(token, ">>", 3)
		|| !ft_strncmp(token, "<", 2)
		|| !ft_strncmp(token, "<<", 3)
		|| !ft_strncmp(token, "&&", 3)
		|| !ft_strncmp(token, "||", 3));
}

/*
** Determines the node type corresponding to a given operator token.
**
** @param token: The operator token to evaluate.
** @return: The corresponding node type.
*/
t_node_type	get_operator_type(const char *token)
{
	if (!ft_strncmp(token, "|", 2))
		return (NODE_PIPE);
	else if (!ft_strncmp(token, ">", 2))
		return (NODE_REDIRECTION_OUT);
	else if (!ft_strncmp(token, ">>", 3))
		return (NODE_REDIRECTION_APPEND);
	else if (!ft_strncmp(token, "<", 2))
		return (NODE_REDIRECTION_IN);
	else if (!ft_strncmp(token, "&&", 3))
		return (NODE_AND);
	else if (!ft_strncmp(token, "||", 3))
		return (NODE_OR);
	else if (!ft_strncmp(token, "<<", 3))
		return (NODE_HEREDOC);
	return (NODE_COMMAND);
}

/*
** Updates the operator priority based on the provided token. If the token
** is an operator, it updates the priority and returns the new priority.
**
** @param token: The operator token to evaluate.
** @param priority: A pointer to the current priority level.
** @return: The new priority level if updated, otherwise 0.
*/
int	update_operator_priority(const char *token, int *priority)
{
	if (!ft_strncmp(token, "&&", 3) || !ft_strncmp(token, "||", 3))
		return (3);
	else if (!ft_strncmp(token, "|", 2) && *priority < 2)
	{
		*priority = 2;
		return (1);
	}
	else if (*priority < 1)
	{
		*priority = 1;
		return (1);
	}
	return (0);
}

/*
** Finds the index of the highest priority operator in the token array
** within the specified range. Returns the index of the operator if found,
** or the index of the last encountered operator with a lower priority.
**
** @param tokens: The array of token strings.
** @param start: The starting index to search.
** @param end: The ending index to search.
** @return: The index of the highest priority operator, or -1 if none found.
*/
int	find_highest_operator(char **tokens, int start, int end)
{
	int	i;
	int	index;
	int	priority;

	i = start;
	index = start;
	priority = 0;
	while (i <= end)
	{
		if (is_operator(tokens[i]))
		{
			if (update_operator_priority(tokens[i], &priority) == 3)
				return (i);
			if (priority > 0)
				index = i;
		}
		i++;
	}
	return (index);
}

/*
** Duplicates a range of tokens from the tokens array and returns a new
** array of strings. Memory for the new array is allocated dynamically.
**
** @param tokens: The array of token strings.
** @param start: The starting index for duplication.
** @param end: The ending index for duplication.
** @return: A new array of duplicated strings, or NULL on failure.
*/
char	**dup_args_range(char **tokens, int start, int end)
{
	int		arg_count;
	char	**new_args;
	int		i;

	arg_count = end - start + 1;
	new_args = (char **)malloc(sizeof(char *) * (arg_count + 1));
	if (!new_args)
		return (NULL);
	i = 0;
	while (start <= end)
	{
		new_args[i] = ft_strdup(tokens[start]);
		if (!new_args[i])
		{
			ft_free_split(new_args);
			return (NULL);
		}
		start++;
		i++;
	}
	new_args[i] = NULL;
	return (new_args);
}
