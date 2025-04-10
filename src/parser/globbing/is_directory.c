/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_directory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <code@cesardelarosa.xyz>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 19:25:38 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/04/10 08:42:06 by cesi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_glob.h"
#include <sys/stat.h>

int	is_directory(const char *path)
{
	struct stat	st;

	return (stat(path, &st) == 0 && ((st.st_mode & S_IFMT) == S_IFDIR));
}
