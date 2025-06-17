/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <code@cesardelarosa.xyz>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 18:08:20 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/06/17 16:50:02 by cesi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"
#include "struct_creation.h"
#include <stdlib.h>

char	*expand_value(char *value, t_token_type type, t_ctx *ctx,
			int *is_multiple);

int	handle_joined_multiple(char *expanded, t_list *last_node)
{
	char	**words;
	char	*joined;
	int		i;

	words = ft_split(expanded, ' ');
	free(expanded);
	if (!words)
		return (0);
	if (words[0])
	{
		joined = ft_strjoin(last_node->content, words[0]);
		if (!joined)
			return (ft_free_split(words), 0);
		free(words[0]);
		free(last_node->content);
		last_node->content = joined;
	}
	i = 1;
	while (words[i])
	{
		ft_lstadd_back(&last_node, ft_lstnew(ft_strdup(words[i])));
		free(words[i]);
		i++;
	}
	return (free(words), 1);
}

int	handle_joined_token(t_list *arg_lst, char *expanded, t_token_type type,
		int is_multiple)
{
	t_list	*last_node;
	char	*joined;

	last_node = ft_lstlast(arg_lst);
	if (type == TOKEN_DOUBLE_QUOTED_STRING || !is_multiple)
	{
		joined = ft_strjoin(last_node->content, expanded);
		free(expanded);
		if (!joined)
			return (0);
		free(last_node->content);
		last_node->content = joined;
		return (1);
	}
	return (handle_joined_multiple(expanded, last_node));
}

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
		ft_lstadd_back(arg_lst, ft_lstnew(ft_strdup(words[i])));
		free(words[i]);
		i++;
	}
	free(words);
	return (1);
}

int	handle_normal_token(t_list **arg_lst, char *expanded, t_token_type type,
		int is_multiple)
{
	if (type == TOKEN_DOUBLE_QUOTED_STRING || !is_multiple)
	{
		ft_lstadd_back(arg_lst, ft_lstnew(expanded));
		return (1);
	}
	return (handle_normal_multiple(arg_lst, expanded));
}

int	parse_word(t_list **arg_lst, t_token *token, t_ctx *ctx)
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
