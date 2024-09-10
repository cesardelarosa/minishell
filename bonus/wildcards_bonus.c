/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <cde-la-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 21:41:59 by cde-la-r          #+#    #+#             */
/*   Updated: 2024/09/08 21:41:59 by cde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <stdlib.h>
#include "libft.h"
#include "minishell.h"

void	ft_realloc_split(char ***split, size_t new_size)
{
	char	**new_split;
	size_t	i;

	new_split = (char **)malloc(sizeof(char *) * new_size);
	if (!new_split)
		return ;
	i = 0;
	while ((*split) && (*split)[i])
	{
		new_split[i] = (*split)[i];
		i++;
	}
	while (i < new_size - 1)
		new_split[i++] = NULL;
	new_split[new_size - 1] = NULL;
	free(*split);
	*split = new_split;
}

void	ft_add_to_split(char ***split, const char *new_item)
{
	size_t	size;

	size = 0;
	while ((*split) && (*split)[size])
		size++;
	ft_realloc_split(split, size + 2);
	(*split)[size] = ft_strdup(new_item);
	(*split)[size + 1] = NULL;
}

int	match_pattern(const char *pattern, const char *filename)
{
	if (*pattern == '\0' && *filename == '\0')
		return (1);
	if (*pattern == '*')
	{
		return (match_pattern(pattern + 1, filename)
			|| (*filename && match_pattern(pattern, filename + 1)));
	}
	if (*pattern == *filename)
		return (match_pattern(pattern + 1, filename + 1));
	return (0);
}

void	add_expanded_wildcards(char ***expanded, const char *pattern)
{
	DIR				*dir;
	struct dirent	*entry;
	int				show_hidden;

	dir = opendir(".");
	if (dir == NULL)
		return ;
	show_hidden = (pattern[0] == '.');
	entry = readdir(dir);
	while (entry)
	{
		if (match_pattern(pattern, entry->d_name)
			&& (show_hidden || entry->d_name[0] != '.')
			&& ft_strncmp(entry->d_name, ".", 2)
			&& ft_strncmp(entry->d_name, "..", 3))
			ft_add_to_split(expanded, entry->d_name);
		entry = readdir(dir);
	}
	closedir(dir);
}

void	expand_wildcards(char ***args)
{
	char	**expanded;
	int		i;

	expanded = (char **)malloc(sizeof(char *));
	if (!expanded)
		return ;
	expanded[0] = NULL;
	i = 0;
	while ((*args)[i])
	{
		if (ft_strchr((*args)[i], '*'))
			add_expanded_wildcards(&expanded, (*args)[i]);
		else
			ft_add_to_split(&expanded, (*args)[i]);
		i++;
	}
	ft_free_split(*args);
	*args = expanded;
}
