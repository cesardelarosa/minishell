/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_value.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <code@cesardelarosa.xyz>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 18:08:20 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/04/05 19:31:20 by cesi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"
#include "struct_creation.h"
#include <stdlib.h>
#include <stdio.h>

char	*expand_value(char *value, t_token_type type, t_ctx *ctx,
		int *is_multiple)
{
	char	*expanded;
	int		i;
	char	*tmp;
	char	*joined;

	*is_multiple = 0;
	if (!value)
		return (ft_strdup(""));
	if (type == TOKEN_SINGLE_QUOTED_STRING)
		return (ft_strdup(value));
	i = 0;
	expanded = ft_strdup("");
	if (!expanded)
		return (NULL);
	while (value[i])
	{
		if (value[i] == '$' && value[i + 1] == '?')
		{
			tmp = ft_itoa(ctx->status);
			if (!tmp)
			{
				free(expanded);
				return (NULL);
			}
			joined = ft_strjoin(expanded, tmp);
			free(expanded);
			free(tmp);
			expanded = joined;
			if (!expanded)
				return (NULL);
			i += 2;
		}
		else if (value[i] == '$' && (ft_isalnum(value[i + 1])
				|| value[i + 1] == '_'))
		{
			int	start = ++i;
			while (value[i] && (ft_isalnum(value[i]) || value[i] == '_'))
				i++;
			char	*var_name = ft_substr(value, start, i - start);
			if (!var_name)
			{
				free(expanded);
				return (NULL);
			}
			char	*var_value = env_get(ctx->env, var_name);
			if (var_value)
			{
				char	*joined = ft_strjoin(expanded, var_value);
				free(expanded);
				expanded = joined;
				if (!expanded)
				{
					free(var_name);
					return (NULL);
				}
				if (type == TOKEN_WORD && ft_strchr(var_value, ' '))
					*is_multiple = 1;
			}
			free(var_name);
		}
		else
		{
			char	addition[2] = {value[i], '\0'};
			char	*joined = ft_strjoin(expanded, addition);
			free(expanded);
			expanded = joined;
			if (!expanded)
				return (NULL);
			i++;
		}
	}
	return (expanded);
}
