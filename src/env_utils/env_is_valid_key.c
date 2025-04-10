/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesi <cesi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 17:40:00 by cesi              #+#    #+#             */
/*   Updated: 2025/04/04 17:40:00 by cesi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "libft.h"

int	env_is_valid_key(const char *key)
{
	int	i;

	if (!key || !*key)
		return (0);
	if (!(ft_isalpha(key[0]) || key[0] == '_'))
		return (0);
	i = 1;
	while (key[i])
	{
		if (!(ft_isalnum(key[i]) || key[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}
