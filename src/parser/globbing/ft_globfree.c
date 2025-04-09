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
#include <stdlib.h>

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
