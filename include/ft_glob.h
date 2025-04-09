/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_glob.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <code@cesardelarosa.xyz>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 12:22:22 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/04/09 12:22:28 by cde-la-r         ###   ########.fr       */
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

int			ft_glob(const char *pattern, int flags, t_ftglob *p);
void		ft_globfree(t_ftglob *p);

#endif
