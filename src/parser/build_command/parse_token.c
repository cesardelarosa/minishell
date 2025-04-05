/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <code@cesardelarosa.xyz>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 18:08:20 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/04/05 19:04:42 by cesi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"
#include "struct_creation.h"
#include <stdlib.h>
#include <stdio.h>

char	*expand_value(char *value, t_token_type type, t_ctx *ctx,
			int *is_multiple);

int	handle_redirection(t_command *cmd, t_list **tokens_ptr,
		t_token_type op_type, t_ctx *ctx);

int	handle_error_token(t_token *token);

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

int	parse_token(t_command *cmd, t_list **tokens_ptr, t_list **arg_lst,
		t_ctx *ctx)
{
	t_token	*token;
	char	*expanded;
	char	**words;
	int		is_multiple;
	int		i;
	char	*joined;

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
		expanded = expand_value(token->value, token->type, ctx, &is_multiple);
		if (!expanded)
			return (0);
		if (token->joined && *arg_lst)
		{
			char	*last_arg = get_last_arg(*arg_lst);
			if (token->type == TOKEN_DOUBLE_QUOTED_STRING || !is_multiple)
			{
				joined = ft_strjoin(last_arg, expanded);
				free(expanded);
				update_last_arg(*arg_lst, joined);
			}
			else
			{
				words = ft_split(expanded, ' ');
				free(expanded);
				if (!words)
					return (0);
				if (words[0])
				{
					joined = ft_strjoin(last_arg, words[0]);
					update_last_arg(*arg_lst, joined);
					free(words[0]);
				}
				i = 1;
				while (words[i])
				{
					add_arg_to_list(arg_lst, words[i]);
					free(words[i]);
					i++;
				}
				free(words);
			}
		}
		else
		{
			if (token->type == TOKEN_DOUBLE_QUOTED_STRING || !is_multiple)
			{
				add_arg_to_list(arg_lst, expanded);
				free(expanded);
			}
			else
			{
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
			}
		}
		*tokens_ptr = (*tokens_ptr)->next;
		return (1);
	}
	*tokens_ptr = (*tokens_ptr)->next;
	return (1);
}
