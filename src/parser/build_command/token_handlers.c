/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <code@cesardelarosa.xyz>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 18:08:20 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/04/09 12:31:18 by cesi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"
#include "struct_creation.h"
#include <stdlib.h>
#include "list_helpers.h"
#include "ft_glob.h"

int	handle_joined_multiple(t_list *arg_lst, char *expanded, char *last_arg)
{
	char	**words;
	char	*joined;
	int		i;
	t_list	**arg_lst_ptr;

	arg_lst_ptr = &arg_lst;
	words = ft_split(expanded, ' ');
	free(expanded);
	if (!words)
		return (0);
	if (words[0])
	{
		joined = ft_strjoin(last_arg, words[0]);
		if (!joined)
			return (ft_free_split(words), 0);
		update_last_arg(arg_lst, joined);
		free(words[0]);
	}
	i = 1;
	while (words[i])
	{
		add_arg_to_list(arg_lst_ptr, words[i]);
		free(words[i++]);
	}
	return (free(words), 1);
}


int	handle_joined_token(t_list *arg_lst, char *expanded, t_token_type type,
		int is_multiple)
{
	char	*last_arg;
	char	*joined;
	t_ftglob	glob_result;

	(void)is_multiple;
	last_arg = get_last_arg(arg_lst);
	if (!last_arg)
		return (0);
	joined = ft_strjoin(last_arg, expanded);
	free(expanded);
	if (!joined)
		return (0);
	if (type == TOKEN_WORD && ft_strchr(joined, '*'))
	{
		if (ft_glob(joined, GLOB_NOCHECK, &glob_result) == 0)
		{
			free(last_arg);
			for (size_t i = 0; i < glob_result.gl_pathc; i++)
				add_arg_to_list(&arg_lst, glob_result.gl_pathv[i]);
			ft_globfree(&glob_result);
		}
		else
		{
			free(last_arg);
			add_arg_to_list(&arg_lst, joined);
		}
	}
	else
	{
		free(last_arg);
		add_arg_to_list(&arg_lst, joined);
	}
	free(joined);
	return (1);
}
/*
int	handle_joined_token(t_list *arg_lst, char *expanded,
		t_token_type type, int is_multiple)
{
	char	*last_arg;
	char	*joined;

	last_arg = get_last_arg(arg_lst);
	if (type == TOKEN_DOUBLE_QUOTED_STRING || !is_multiple)
	{
		joined = ft_strjoin(last_arg, expanded);
		free(expanded);
		if (!joined)
			return (0);
		update_last_arg(arg_lst, joined);
		return (1);
	}
	return (handle_joined_multiple(arg_lst, expanded, last_arg));
}*/

int	handle_normal_multiple(t_list **arg_lst, char *expanded, t_token_type type)
{
	char	**words;
	int		i;
	t_ftglob	glob_result;

	words = ft_split(expanded, ' ');
	free(expanded);
	if (!words)
		return (0);
	i = 0;
	while (words[i])
	{
		if (type == TOKEN_WORD && ft_strchr(words[i], '*'))
		{
			if (ft_glob(words[i], GLOB_NOCHECK, &glob_result) == 0)
			{
				for (size_t j = 0; j < glob_result.gl_pathc; j++)
					add_arg_to_list(arg_lst, glob_result.gl_pathv[j]);
				ft_globfree(&glob_result);
			}
			else
				add_arg_to_list(arg_lst, words[i]);
		}
		else
			add_arg_to_list(arg_lst, words[i]);
		i++;
	}
	free(words);
	return (1);
}
/*
int	handle_normal_multiple(t_list **arg_lst, char *expanded)
{
	char	**words;
	int		i;

	words = ft_split(expanded, ' ');
	free(expanded);
	if (!words)
		return (0);
	i = 0;
	while (words[i])
	{
		add_arg_to_list(arg_lst, words[i]);
		free(words[i]);
		i++;
	}
	free(words);
	return (1);
}*/

int	handle_normal_token(t_list **arg_lst, char *expanded, t_token_type type,
		int is_multiple)
{
	t_ftglob	glob_result;

	if (type == TOKEN_DOUBLE_QUOTED_STRING || !is_multiple)
	{
		if (type == TOKEN_WORD && ft_strchr(expanded, '*'))
		{
			if (ft_glob(expanded, GLOB_NOCHECK, &glob_result) == 0)
			{
				for (size_t i = 0; i < glob_result.gl_pathc; i++)
					add_arg_to_list(arg_lst, glob_result.gl_pathv[i]);
				ft_globfree(&glob_result);
			}
			else
				add_arg_to_list(arg_lst, expanded);
			free(expanded);
			return (1);
		}
		add_arg_to_list(arg_lst, expanded);
		free(expanded);
		return (1);
	}
	return (handle_normal_multiple(arg_lst, expanded, type));
}
/*
int	handle_normal_token(t_list **arg_lst, char *expanded,
		t_token_type type, int is_multiple)
{
	if (type == TOKEN_DOUBLE_QUOTED_STRING || !is_multiple)
	{
		add_arg_to_list(arg_lst, expanded);
		free(expanded);
		return (1);
	}
	return (handle_normal_multiple(arg_lst, expanded));
}*/

int	process_word_token(t_list **arg_lst, t_token *token, t_ctx *ctx)
{
	char	*expanded;
	int		is_multiple;
	int		result;

	expanded = expand_value(token->value, token->type, ctx, &is_multiple);
	if (!expanded)
		return (0);
	if (token->joined && *arg_lst)
		result = handle_joined_token(*arg_lst, expanded, token->type,
				is_multiple);
	else
		result = handle_normal_token(arg_lst, expanded, token->type,
				is_multiple);
	return (result);
}
