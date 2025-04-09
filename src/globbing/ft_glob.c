/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_glob.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <code@cesardelarosa.xyz>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 12:23:20 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/04/09 12:23:22 by cde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_glob.h"
#include "libft.h"
#include <dirent.h>
#include <stdlib.h>

static int	match_pattern(const char *pattern, const char *str)
{
	if (!*pattern)
		return (!*str);
	if (*pattern == '*')
	{
		while (*pattern == '*')
			pattern++;
		if (!*pattern)
			return (1);
		while (*str)
		{
			if (match_pattern(pattern, str))
				return (1);
			str++;
		}
		return (0);
	}
	else
	{
		if (*str && (*pattern == *str))
			return (match_pattern(pattern + 1, str + 1));
		return (0);
	}
}

int	ft_glob(const char *pattern, int flags, t_ftglob *p)
{
	DIR				*dir;
	struct dirent	*entry;
	char			**matches;
	size_t			count;
	size_t			capacity;

	if (ft_strchr(pattern, '/'))
	{
		p->gl_pathc = 1;
		p->gl_pathv = malloc(sizeof(char *) * 2);
		if (!p->gl_pathv)
			return (1);
		p->gl_pathv[0] = ft_strdup(pattern);
		p->gl_pathv[1] = NULL;
		return (0);
	}

	capacity = 10;
	matches = malloc(sizeof(char *) * capacity);
	if (!matches)
		return (1);
	count = 0;
	dir = opendir(".");
	if (!dir)
	{
		free(matches);
		return (1);
	}
	while ((entry = readdir(dir)) != NULL)
	{
		if (pattern[0] != '.' && entry->d_name[0] == '.')
			continue;
		if (match_pattern(pattern, entry->d_name))
		{
			if (count >= capacity)
			{
				capacity *= 2;
				matches = realloc(matches, sizeof(char *) * capacity);
				if (!matches)
				{
					closedir(dir);
					return (1);
				}
			}
			matches[count++] = ft_strdup(entry->d_name);
		}
	}
	closedir(dir);
	if (count == 0 && (flags & GLOB_NOCHECK))
	{
		matches[0] = ft_strdup(pattern);
		count = 1;
	}
	matches = realloc(matches, sizeof(char *) * (count + 1));
	if (!matches)
		return (1);
	matches[count] = NULL;
	p->gl_pathc = count;
	p->gl_pathv = matches;
	return (0);
}

void	ft_globfree(t_ftglob *p)
{
	size_t	i;

	if (!p || !p->gl_pathv)
		return;
	i = 0;
	while (i < p->gl_pathc)
	{
		free(p->gl_pathv[i]);
		i++;
	}
	free(p->gl_pathv);
	p->gl_pathv = NULL;
	p->gl_pathc = 0;
}
