/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <code@cesardelarosa.xyz>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 13:16:49 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/06/24 23:24:04 by cde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"
#include "struct_creation.h"
#include <stdio.h>
#include <stdlib.h>

int			parse_token(t_command *cmd, t_list **tokens_ptr, t_list **arg_lst,
				t_ctx *ctx);

static int	is_command_part(t_token_type type)
{
	return (type == TOKEN_WORD
		|| type == TOKEN_SINGLE_QUOTED_STRING
		|| type == TOKEN_DOUBLE_QUOTED_STRING
		|| type == TOKEN_REDIRECT_IN
		|| type == TOKEN_REDIRECT_OUT
		|| type == TOKEN_HEREDOC
		|| type == TOKEN_APPEND);
}

static char	**build_argv_from_list(t_list *lst)
{
	size_t	count;
	size_t	i;
	char	**argv;
	t_list	*current;

	count = ft_lstsize(lst);
	argv = ft_calloc(count + 1, sizeof(char *));
	if (!argv)
		return (NULL);
	i = 0;
	current = lst;
	while (current)
	{
		argv[i++] = ft_strdup((char *)current->content);
		current = current->next;
	}
	argv[i] = NULL;
	return (argv);
}

t_command	*parse_command(t_list **tokens_ptr, t_ctx *ctx,
	t_token_parser_ft parse_ft)
{
	t_command	*cmd;
	t_list		*arg_list;
	t_token		*token;

	cmd = ft_calloc(1, sizeof(t_command));
	if (!cmd)
		return (NULL);
	arg_list = NULL;
	while (*tokens_ptr)
	{
		token = (t_token *)(*tokens_ptr)->content;
		if (!is_command_part(token->type))
			break ;
		if (parse_ft(cmd, tokens_ptr, &arg_list, ctx) != 1)
		{
			command_destroy(cmd);
			ft_lstclear(&arg_list, free);
			return (NULL);
		}
	}
	cmd->argv = build_argv_from_list(arg_list);
	ft_lstclear(&arg_list, free);
	if (!cmd->argv || !cmd->argv[0])
		return (command_destroy(cmd), NULL);
	return (cmd);
}
