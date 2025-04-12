/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_path_pattern.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <code@cesardelarosa.xyz>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 08:33:58 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/04/10 08:35:16 by cde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_glob_bonus.h"
#include "libft.h"
#include <stdlib.h>

static int	finalize_matches(t_matches *m, int flags, const char *pattern)
{
	char	**temp;

	if (m->count == 0 && (flags & GLOB_NOCHECK))
	{
		m->matches[0] = ft_strdup(pattern);
		if (!m->matches[0])
			return (1);
		m->count = 1;
	}
	temp = realloc(m->matches, sizeof(char *) * (m->count + 1));
	if (!temp)
		return (1);
	m->matches = temp;
	m->matches[m->count] = NULL;
	bubble_sort(m->matches, m->count);
	return (0);
}

static int	init_glob_context(t_glob_context *ctx, t_matches *m,
							const char *pattern)
{
	ctx->segments = ft_split(pattern, '/');
	if (!ctx->segments || !init_matches(&m->matches, &m->capacity))
	{
		ft_free_split(ctx->segments);
		return (0);
	}
	ctx->results = &m->matches;
	ctx->res_count = &m->count;
	ctx->res_capacity = &m->capacity;
	return (1);
}

static void	cleanup_resources(t_glob_context *ctx, t_matches *m)
{
	ft_free_split(ctx->segments);
	while (m->count--)
		free(m->matches[m->count]);
	free(m->matches);
}

static int	perform_glob(t_glob_context *ctx, t_matches *m)
{
	if (!recursive_glob(".", ctx, 0))
	{
		cleanup_resources(ctx, m);
		return (0);
	}
	ft_free_split(ctx->segments);
	return (1);
}

int	handle_path_pattern(const char *pattern, int flags, t_ftglob *p)
{
	t_glob_context	ctx;
	t_matches		m;

	m.capacity = 0;
	m.count = 0;
	if (!init_glob_context(&ctx, &m, pattern))
		return (1);
	if (!perform_glob(&ctx, &m))
		return (1);
	if (finalize_matches(&m, flags, pattern))
		return (1);
	p->gl_pathc = m.count;
	p->gl_pathv = m.matches;
	return (0);
}
