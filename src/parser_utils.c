/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 14:51:46 by cde-la-r          #+#    #+#             */
/*   Updated: 2024/10/01 15:03:54 by cde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

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
	return (NODE_UNKNOWN);
}

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

int	find_highest_operator(char **tokens, int start, int end)
{
	int	i;
	int	index;
	int	priority;

	i = start;
	index = -1;
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
