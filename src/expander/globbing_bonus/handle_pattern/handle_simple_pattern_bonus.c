/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_simple_pattern_bonus.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <code@cesardelarosa.xyz>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 08:36:02 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/06/17 21:14:51 by cde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_glob_bonus.h"
#include "libft.h"
#include <dirent.h>
#include <stdlib.h>

static int	add_matching_entry(const char *entry_name, t_matches *m)
{
	char	*dup;

	dup = ft_strdup(entry_name);
	return (dup && add_match(&m->matches, &m->count, &m->capacity, dup));
}

static int	process_entry(struct dirent *entry, const char *pattern,
	t_matches *m)
{
	if (pattern[0] != '.' && entry->d_name[0] == '.')
		return (1);
	if (match_pattern(pattern, entry->d_name))
		return (add_matching_entry(entry->d_name, m));
	return (1);
}

static int	init_dir_and_matches(DIR **dir, t_matches *m)
{
	m->capacity = 0;
	m->count = 0;
	*dir = opendir(".");
	if (!*dir || !init_matches(&m->matches, &m->capacity))
	{
		if (*dir)
			closedir(*dir);
		return (0);
	}
	return (1);
}

static int	process_entries(DIR *dir, const char *pattern, t_matches *m)
{
	struct dirent	*entry;

	entry = readdir(dir);
	while (entry && process_entry(entry, pattern, m))
		entry = readdir(dir);
	return (1);
}

int	handle_simple_pattern(const char *pattern, int flags, t_ftglob *p)
{
	DIR			*dir;
	t_matches	m;

	if (!init_dir_and_matches(&dir, &m))
		return (1);
	process_entries(dir, pattern, &m);
	closedir(dir);
	if (!m.count && (flags & (1 << 0)))
	{
		m.matches[0] = ft_strdup(pattern);
		if (!m.matches[0])
			return (1);
		m.count = 1;
	}
	m.matches = realloc(m.matches, sizeof(char *) * (m.count + 1));
	if (!m.matches)
		return (1);
	m.matches[m.count] = NULL;
	bubble_sort(m.matches, m.count);
	p->gl_pathc = m.count;
	p->gl_pathv = m.matches;
	return (0);
}
