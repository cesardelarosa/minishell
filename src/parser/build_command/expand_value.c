/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_value.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <code@cesardelarosa.xyz>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 18:08:20 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/04/05 21:55:54 by cesi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"
#include "struct_creation.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct s_expand_data
{
	char			*expanded;
	int				is_multiple;
	t_token_type	type;
	t_ctx			*ctx;
}	t_expand_data;

static int	append_char(t_expand_data *data, char c)
{
	char	addition[2];
	char	*joined;

	addition[0] = c;
	addition[1] = '\0';
	joined = ft_strjoin(data->expanded, addition);
	if (!joined)
		return (0);
	free(data->expanded);
	data->expanded = joined;
	return (1);
}

static int	expand_exit_status(t_expand_data *data, int *i)
{
	char	*status_str;
	char	*joined;

	status_str = ft_itoa(data->ctx->status);
	if (!status_str)
		return (0);
	joined = ft_strjoin(data->expanded, status_str);
	free(status_str);
	if (!joined)
		return (0);
	free(data->expanded);
	data->expanded = joined;
	*i += 2;
	return (1);
}

static int	expand_env_variable(t_expand_data *data, char *value, int *i)
{
	char	*var_name;
	char	*var_value;
	char	*joined;
	int		start;

	start = ++(*i);
	while (value[*i] && (ft_isalnum(value[*i]) || value[*i] == '_'))
		(*i)++;
	var_name = ft_substr(value, start, *i - start);
	if (!var_name)
		return (0);
	var_value = env_get(data->ctx->env, var_name);
	if (var_value)
	{
		joined = ft_strjoin(data->expanded, var_value);
		free(data->expanded);
		data->expanded = joined;
		if (!joined)
			return (free(var_name), 0);
		if (data->type == TOKEN_WORD && ft_strchr(var_value, ' '))
			data->is_multiple = 1;
	}
	free(var_name);
	return (1);
}

static int	handle_character(t_expand_data *data, char *value, int *i)
{
	if (value[*i] == '$' && value[*i + 1] == '?')
		return (expand_exit_status(data, i));
	else if (value[*i] == '$' && (ft_isalnum(value[*i + 1])
			|| value[*i + 1] == '_'))
		return (expand_env_variable(data, value, i));
	else
	{
		if (!append_char(data, value[*i]))
			return (0);
		(*i)++;
		return (1);
	}
}

char	*expand_value(char *value, t_token_type type, t_ctx *ctx,
		int *is_multiple)
{
	t_expand_data	data;
	int				i;

	data.is_multiple = 0;
	data.type = type;
	data.ctx = ctx;
	if (!value)
		return (ft_strdup(""));
	if (type == TOKEN_SINGLE_QUOTED_STRING)
		return (ft_strdup(value));
	i = 0;
	data.expanded = ft_strdup("");
	if (!data.expanded)
		return (NULL);
	while (value[i])
	{
		if (!handle_character(&data, value, &i))
			return (free(data.expanded), NULL);
	}
	*is_multiple = data.is_multiple;
	return (data.expanded);
}
