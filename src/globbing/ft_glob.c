/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_glob.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <code@cesardelarosa.xyz>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 12:23:20 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/04/09 14:06:35 by cesi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_glob.h"
#include "libft.h"
#include <dirent.h>
#include <stdlib.h>
#include <sys/stat.h>

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
	if (*pattern != *str)
		return (0);
	return (match_pattern(pattern + 1, str + 1));
}

static int	is_directory(const char *path)
{
	struct stat	st;

	return (stat(path, &st) == 0 && ((st.st_mode & S_IFMT) == S_IFDIR));
}

static char	*join_path(const char *base, const char *name)
{
	char	*temp;
	char	*res;

	temp = ft_strjoin(base, "/");
	if (!temp)
		return (NULL);
	res = ft_strjoin(temp, name);
	free(temp);
	return (res);
}

static int	recursive_glob(const char *base, char **segments, int seg_index,
		char ***results, size_t *res_count, size_t *res_capacity)
{
	DIR				*dir;
	struct dirent	*entry;
	char			*new_path;
	char			**temp;

	dir = opendir(base);
	if (!dir)
		return (0);
	while ((entry = readdir(dir)) != NULL)
	{
		if (segments[seg_index][0] != '.' && entry->d_name[0] == '.')
			continue ;
		if (match_pattern(segments[seg_index], entry->d_name))
		{
			new_path = join_path(base, entry->d_name);
			if (!new_path)
			{
				closedir(dir);
				return (0);
			}
			if (segments[seg_index + 1])
			{
				if (is_directory(new_path))
				{
					if (!recursive_glob(new_path, segments, seg_index + 1,
							results, res_count, res_capacity))
					{
						free(new_path);
						closedir(dir);
						return (0);
					}
				}
				free(new_path);
			}
			else
			{
				if (*res_count >= *res_capacity)
				{
					*res_capacity *= 2;
					temp = realloc(*results, sizeof(char *) * (*res_capacity));
					if (!temp)
					{
						free(new_path);
						closedir(dir);
						return (0);
					}
					*results = temp;
				}
				(*results)[*res_count] = new_path;
				(*res_count)++;
			}
		}
	}
	closedir(dir);
	return (1);
}

static void	bubble_sort(char **arr, size_t count)
{
	char	*temp;
	size_t	i;
	size_t	j;

	i = 0;
	while (i < count)
	{
		j = 0;
		while (j < count - i - 1)
		{
			if (ft_strcmp(arr[j], arr[j + 1]) > 0)
			{
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}

int	ft_glob(const char *pattern, int flags, t_ftglob *p)
{
	char			**matches;
	char			**segments;
	DIR				*dir;
	struct dirent	*entry;
	char			**temp;
	size_t			count;
	size_t			capacity;

	capacity = 10;
	if (ft_strchr(pattern, '/'))
	{
		segments = ft_split(pattern, '/');
		if (!segments)
			return (1);
		matches = malloc(sizeof(char *) * capacity);
		if (!matches)
		{
			ft_free_split(segments);
			return (1);
		}
		count = 0;
		if (!recursive_glob(".", segments, 0, &matches, &count, &capacity))
		{
			ft_free_split(segments);
			for (size_t i = 0; i < count; i++)
				free(matches[i]);
			free(matches);
			return (1);
		}
		ft_free_split(segments);
		if (count == 0 && (flags & GLOB_NOCHECK))
		{
			matches[0] = ft_strdup(pattern);
			count = 1;
		}
		matches = realloc(matches, sizeof(char *) * (count + 1));
		if (!matches)
			return (1);
		matches[count] = NULL;
		bubble_sort(matches, count);
		p->gl_pathc = count;
		p->gl_pathv = matches;
		return (0);
	}
	matches = malloc(sizeof(char *) * capacity);
	if (!matches)
		return (1);
	count = 0;
	{
		dir = opendir(".");
		if (!dir)
		{
			free(matches);
			return (1);
		}
		while ((entry = readdir(dir)) != NULL)
		{
			if (pattern[0] != '.' && entry->d_name[0] == '.')
				continue ;
			if (match_pattern(pattern, entry->d_name))
			{
				if (count >= capacity)
				{
					capacity *= 2;
					temp = realloc(matches, sizeof(char *) * capacity);
					if (!temp)
					{
						closedir(dir);
						return (1);
					}
					matches = temp;
				}
				matches[count++] = ft_strdup(entry->d_name);
			}
		}
		closedir(dir);
	}
	if (count == 0 && (flags & GLOB_NOCHECK))
	{
		matches[0] = ft_strdup(pattern);
		count = 1;
	}
	matches = realloc(matches, sizeof(char *) * (count + 1));
	if (!matches)
		return (1);
	matches[count] = NULL;
	bubble_sort(matches, count);
	p->gl_pathc = count;
	p->gl_pathv = matches;
	return (0);
}

void	ft_globfree(t_ftglob *p)
{
	size_t	i;

	if (!p || !p->gl_pathv)
		return ;
	i = 0;
	while (i < p->gl_pathc)
		free(p->gl_pathv[i++]);
	free(p->gl_pathv);
	p->gl_pathv = NULL;
	p->gl_pathc = 0;
}
