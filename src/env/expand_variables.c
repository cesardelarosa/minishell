/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <code@cesardelarosa.xyz>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 00:21:37 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/04/04 00:21:48 by cde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "libft.h"
#include <stdlib.h>

char	*expand_variables(t_env *env, const char *input)
{
	char	*result;
	size_t	i;
	char	*tmp;
	char	*var_value;
	char	*var_name;
	size_t	start;
	char	letter[2];

	result = ft_strdup("");
	i = 0;
	while (input[i])
	{
		if (input[i] == '$')
		{
			i++;
			start = i;
			while (ft_isalnum(input[i]) || input[i] == '_')
				i++;
			var_name = ft_substr(input, start, i - start);
			var_value = env_get(env, var_name);
			free(var_name);
			if (var_value)
			{
				tmp = result;
				result = ft_strjoin(result, var_value);
				free(tmp);
			}
		}
		else
		{
			tmp = result;
			{
				letter[0] = input[i];
				letter[1] = '\0';
				result = ft_strjoin(result, letter);
			}
			free(tmp);
			i++;
		}
	}
	return (result);
}
