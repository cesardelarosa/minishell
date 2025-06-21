/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_globbing_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <code@cesardelarosa.xyz>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 17:42:42 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/06/22 00:23:30 by cde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_glob_bonus.h"
#include "libft.h"
#include <dirent.h>
#include <stdlib.h>
#include <sys/stat.h>

static int	ft_glob(const char *pattern, int flags, t_ftglob *p)
{
	if (ft_strchr(pattern, '/'))
		return (handle_path_pattern(pattern, flags, p));
	return (handle_simple_pattern(pattern, flags, p));
}

static void	ft_globfree(t_ftglob *p)
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

int	handle_globbing(t_list **args_lst, char *pattern)
{
	t_ftglob	glob_result;
	size_t		i;

	if (ft_glob(pattern, 0, &glob_result))
	{
		free(pattern);
		return (0);
	}
	if (glob_result.gl_pathc)
	{
		i = 0;
		while (i < glob_result.gl_pathc)
			ft_lstadd_back(args_lst,
				ft_lstnew(ft_strdup(glob_result.gl_pathv[i++])));
	}
	else
		ft_lstadd_back(args_lst, ft_lstnew(ft_strdup(pattern)));
	free(pattern);
	ft_globfree(&glob_result);
	return (1);
}
