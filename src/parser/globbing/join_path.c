/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <code@cesardelarosa.xyz>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 19:27:05 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/04/09 19:27:06 by cde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*join_path(const char *base, const char *name)
{
	char	*temp;
	char	*res;

	temp = ft_strjoin(base, "/");
	if (!temp)
		return (NULL);
	res = ft_strjoin(temp, name);
	free(temp);
	return (res);
}
