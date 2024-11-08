/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strarray_dup.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <cde-la-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 11:55:31 by cde-la-r          #+#    #+#             */
/*   Updated: 2024/10/28 11:55:32 by cde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	**ft_strarray_dup(char **tokens, size_t start, size_t end)
{
	size_t	i;
	size_t	len;
	char	**dup;

	len = 0;
	while (tokens[len])
		len++;
	end -= (end - len + 1) * (end >= len);
	if (start > end)
		return (NULL);
	dup = malloc((end - start + 2) * sizeof(char *));
	if (dup == NULL)
		return (NULL);
	i = 0;
	while (start <= end)
	{
		dup[i] = ft_strdup(tokens[start++]);
		if (dup[i++] == NULL)
		{
			ft_free_split(dup);
			return (NULL);
		}
	}
	dup[i] = NULL;
	return (dup);
}
