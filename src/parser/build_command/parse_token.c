/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <code@cesardelarosa.xyz>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 18:08:20 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/04/05 22:11:16 by cesi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"
#include "struct_creation.h"
#include <stdio.h>
#include <stdlib.h>

char		*expand_value(char *value, t_token_type type, t_ctx *ctx,
				int *is_multiple);

int			handle_redirection(t_command *cmd, t_list **tokens_ptr,
				t_token_type op_type, t_ctx *ctx);

int			handle_error_token(t_token *token);

static void	add_arg_to_list(t_list **arg_lst, char *arg);
static char	*get_last_arg(t_list *arg_lst);
static void	update_last_arg(t_list *arg_lst, char *new_content);
static int	handle_joined_multiple(t_list *arg_lst, char *expanded,
				char *last_arg);
static int	handle_joined_token(t_list *arg_lst, char *expanded,
				t_token_type type, int is_multiple);
static int	handle_normal_multiple(t_list **arg_lst, char *expanded);
static int	handle_normal_token(t_list **arg_lst, char *expanded,
				t_token_type type, int is_multiple);
static int	process_word_token(t_list **arg_lst, t_token *token, t_ctx *ctx);

static void	add_arg_to_list(t_list **arg_lst, char *arg)
{
	if (arg && *arg)
		ft_lstadd_back(arg_lst, ft_lstnew(ft_strdup(arg)));
}

static char	*get_last_arg(t_list *arg_lst)
{
	t_list	*current;

	if (!arg_lst)
		return (NULL);
	current = arg_lst;
	while (current->next)
		current = current->next;
	return ((char *)current->content);
}

static void	update_last_arg(t_list *arg_lst, char *new_content)
{
	t_list	*current;

	if (!arg_lst || !new_content)
		return ;
	current = arg_lst;
	while (current->next)
		current = current->next;
	free(current->content);
	current->content = new_content;
}

static int	handle_joined_multiple(t_list *arg_lst, char *expanded,
		char *last_arg)
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

static int	handle_joined_token(t_list *arg_lst, char *expanded,
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
}

static int	handle_normal_multiple(t_list **arg_lst, char *expanded)
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
}

static int	handle_normal_token(t_list **arg_lst, char *expanded,
		t_token_type type, int is_multiple)
{
	if (type == TOKEN_DOUBLE_QUOTED_STRING || !is_multiple)
	{
		add_arg_to_list(arg_lst, expanded);
		free(expanded);
		return (1);
	}
	return (handle_normal_multiple(arg_lst, expanded));
}

static int	process_word_token(t_list **arg_lst, t_token *token, t_ctx *ctx)
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

int	parse_token(t_command *cmd, t_list **tokens_ptr, t_list **arg_lst,
		t_ctx *ctx)
{
	t_token	*token;
	int		result;

	token = (t_token *)(*tokens_ptr)->content;
	if (token->type == TOKEN_REDIRECT_IN || token->type == TOKEN_REDIRECT_OUT
		|| token->type == TOKEN_HEREDOC || token->type == TOKEN_APPEND)
		return (handle_redirection(cmd, tokens_ptr, token->type, ctx));
	else if (token->type == TOKEN_ERROR)
		return (handle_error_token(token));
	else if (token->type == TOKEN_WORD
		|| token->type == TOKEN_SINGLE_QUOTED_STRING
		|| token->type == TOKEN_DOUBLE_QUOTED_STRING)
	{
		result = process_word_token(arg_lst, token, ctx);
		*tokens_ptr = (*tokens_ptr)->next;
		return (result);
	}
	*tokens_ptr = (*tokens_ptr)->next;
	return (1);
}
