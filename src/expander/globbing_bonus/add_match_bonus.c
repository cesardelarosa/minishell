/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_match.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <code@cesardelarosa.xyz>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 08:43:56 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/04/12 12:15:16 by cesi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_glob_bonus.h"
#include <stdlib.h>

int	add_match(char ***results, size_t *res_count, size_t *res_capacity,
		char *new_path)
{
	char	**temp;

	if (*res_count >= *res_capacity)
	{
		*res_capacity *= 2;
		temp = realloc(*results, sizeof(char *) * (*res_capacity));
		if (!temp)
			return (0);
		*results = temp;
	}
	(*results)[*res_count] = new_path;
	(*res_count)++;
	return (1);
}
