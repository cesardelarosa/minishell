/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_glob.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <code@cesardelarosa.xyz>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 12:23:20 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/04/09 15:39:01 by cesi             ###   ########.fr       */
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

static int	add_match(char ***results, size_t *res_count, size_t *res_capacity,
		char *new_path)
{
	char	**temp;

	if (*res_count >= *res_capacity)
	{
		*res_capacity *= 2;
		temp = realloc(*results, sizeof(char *) * (*res_capacity));
		if (!temp)
			return (0);
		*results = temp;
	}
	(*results)[*res_count] = new_path;
	(*res_count)++;
	return (1);
}

static int	recursive_glob(const char *base, t_glob_context *ctx, int seg_index)
{
	DIR				*dir;
	struct dirent	*entry;
	char			*new_path;

	dir = opendir(base);
	if (!dir)
		return (0);
	while (1)
	{
		entry = readdir(dir);
		if (!entry)
			break ;
		if (ctx->segments[seg_index][0] != '.' && entry->d_name[0] == '.')
			continue ;
		if (match_pattern(ctx->segments[seg_index], entry->d_name))
		{
			new_path = join_path(base, entry->d_name);
			if (!new_path)
			{
				closedir(dir);
				return (0);
			}
			if (ctx->segments[seg_index + 1])
			{
				if (is_directory(new_path))
				{
					if (!recursive_glob(new_path, ctx, seg_index + 1))
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
				if (!add_match(ctx->results, ctx->res_count, ctx->res_capacity,
						new_path))
				{
					free(new_path);
					closedir(dir);
					return (0);
				}
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

static int	init_matches(char ***matches, size_t *capacity)
{
	*capacity = 10;
	*matches = malloc(sizeof(char *) * (*capacity));
	return (*matches != NULL);
}

static int	handle_path_pattern(const char *pattern, int flags, t_ftglob *p)
{
	char			**matches;
	t_glob_context	ctx;
	size_t			count;
	size_t			capacity;
	size_t			i;

	ctx.segments = ft_split(pattern, '/');
	if (!ctx.segments)
		return (1);
	if (!init_matches(&matches, &capacity))
	{
		ft_free_split(ctx.segments);
		return (1);
	}
	count = 0;
	ctx.results = &matches;
	ctx.res_count = &count;
	ctx.res_capacity = &capacity;
	if (!recursive_glob(".", &ctx, 0))
	{
		ft_free_split(ctx.segments);
		while (i < count)
			free(matches[i++]);
		free(matches);
		return (1);
	}
	ft_free_split(ctx.segments);
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

static int	handle_simple_pattern(const char *pattern, int flags, t_ftglob *p)
{
	char			**matches;
	DIR				*dir;
	struct dirent	*entry;
	size_t			count;
	size_t			capacity;

	if (!init_matches(&matches, &capacity))
		return (1);
	count = 0;
	dir = opendir(".");
	if (!dir)
	{
		free(matches);
		return (1);
	}
	while (1)
	{
		entry = readdir(dir);
		if (entry == NULL)
			break ;
		if (pattern[0] != '.' && entry->d_name[0] == '.')
			continue ;
		if (match_pattern(pattern, entry->d_name))
		{
			if (!add_match(&matches, &count, &capacity,
					ft_strdup(entry->d_name)))
			{
				closedir(dir);
				return (1);
			}
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
	bubble_sort(matches, count);
	p->gl_pathc = count;
	p->gl_pathv = matches;
	return (0);
}

int	ft_glob(const char *pattern, int flags, t_ftglob *p)
{
	if (ft_strchr(pattern, '/'))
		return (handle_path_pattern(pattern, flags, p));
	else
		return (handle_simple_pattern(pattern, flags, p));
}
