/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_globbing_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <code@cesardelarosa.xyz>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 17:42:42 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/06/09 17:56:24 by cesi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_glob_bonus.h"
#include "libft.h"

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
