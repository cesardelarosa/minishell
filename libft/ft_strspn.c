/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strspn.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <code@cesardelarosa.xyz>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 14:38:08 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/04/01 14:38:11 by cde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strspn(const char *str, const char *accept)
{
	const char	*p;
	const char	*a;
	size_t		count;

	count = 0;
	p = str;
	while (*p)
	{
		a = accept;
		while (*a)
		{
			if (*p == *a)
				break ;
			a++;
		}
		if (!*a)
			return (count);
		count++;
		p++;
	}
	return (count);
}
