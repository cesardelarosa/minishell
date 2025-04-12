/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_matches.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <code@cesardelarosa.xyz>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 08:33:09 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/04/10 08:42:49 by cesi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>

int	init_matches(char ***matches, size_t *capacity)
{
	*capacity = 10;
	*matches = malloc(sizeof(char *) * (*capacity));
	return (*matches != NULL);
}
