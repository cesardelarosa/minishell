/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursive_glob.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <code@cesardelarosa.xyz>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 19:35:16 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/04/10 08:41:11 by cesi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_glob.h"
#include <dirent.h>
#include <stdlib.h>

static int	handle_new_path(char *new_path, t_glob_context *ctx, int seg_index)
{
	if (ctx->segments[seg_index + 1])
	{
		if (is_directory(new_path) && !recursive_glob(new_path, ctx, seg_index
				+ 1))
		{
			free(new_path);
			return (0);
		}
		free(new_path);
	}
	else if (!add_match(ctx->results, ctx->res_count, ctx->res_capacity,
			new_path))
	{
		free(new_path);
		return (0);
	}
	return (1);
}

static int	process_entry(struct dirent *entry, const char *base,
		t_glob_context *ctx, int seg_index)
{
	char	*new_path;
	int		result;

	if (ctx->segments[seg_index][0] != '.' && entry->d_name[0] == '.')
		return (1);
	if (!match_pattern(ctx->segments[seg_index], entry->d_name))
		return (1);
	new_path = join_path(base, entry->d_name);
	if (!new_path)
		return (0);
	result = handle_new_path(new_path, ctx, seg_index);
	if (!result)
		free(new_path);
	return (result);
}

int	recursive_glob(const char *base, t_glob_context *ctx, int seg_index)
{
	DIR				*dir;
	struct dirent	*entry;
	int				success;

	dir = opendir(base);
	if (!dir)
		return (0);
	success = 1;
	while (success)
	{
		entry = readdir(dir);
		if (!entry)
			break ;
		success = process_entry(entry, base, ctx, seg_index);
	}
	closedir(dir);
	return (success);
}
