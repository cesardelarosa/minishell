/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_glob.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <code@cesardelarosa.xyz>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 12:23:20 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/04/10 08:35:48 by cesi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_glob_bonus.h"
#include "libft.h"
#include <dirent.h>
#include <stdlib.h>
#include <sys/stat.h>

int	ft_glob(const char *pattern, int flags, t_ftglob *p)
{
	if (ft_strchr(pattern, '/'))
		return (handle_path_pattern(pattern, flags, p));
	else
		return (handle_simple_pattern(pattern, flags, p));
}
