/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_glob.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <code@cesardelarosa.xyz>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 12:22:22 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/04/10 08:40:19 by cesi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_GLOB_H
# define FT_GLOB_H

# include <stddef.h>

# define GLOB_NOCHECK (1 << 0)

typedef struct s_ftglob
{
	size_t	gl_pathc;
	char	**gl_pathv;
}			t_ftglob;

typedef struct s_glob_context
{
	char	**segments;
	char	***results;
	size_t	*res_count;
	size_t	*res_capacity;
}			t_glob_context;

typedef struct s_matches
{
	char	**matches;
	size_t	count;
	size_t	capacity;
}	t_matches;

int			match_pattern(const char *pattern, const char *str);
int			is_directory(const char *path);
char		*join_path(const char *base, const char *name);
int			add_match(char ***results, size_t *res_count, size_t *res_capacity,
				char *new_path);
int			recursive_glob(const char *base, t_glob_context *ctx,
				int seg_index);
void		bubble_sort(char **arr, size_t count);
int			init_matches(char ***matches, size_t *capacity);
int			handle_path_pattern(const char *pattern, int flags, t_ftglob *p);
int			handle_simple_pattern(const char *pattern, int flags, t_ftglob *p);
int			ft_glob(const char *pattern, int flags, t_ftglob *p);
void		ft_globfree(t_ftglob *p);

#endif
