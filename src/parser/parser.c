/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <code@cesardelarosa.xyz>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 18:08:20 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/04/03 23:01:38 by cesi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "struct_creation.h"
#include <stdio.h>
#include <stdlib.h>
#include "lexer.h"

int	process_token(t_command *cmd, t_list **tokens_ptr, t_list **arg_lst);

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

static t_command	*build_command(t_list **tokens_ptr, int status)
{
	t_command	*cmd;
	t_list		*arg_list;
	t_token		*token;

	(void)status;
	cmd = ft_calloc(1, sizeof(t_command));
	if (!cmd)
		return (NULL);
	arg_list = NULL;
	while (*tokens_ptr)
	{
		token = (t_token *)(*tokens_ptr)->content;
		if (token->type == TOKEN_PIPE || token->type == TOKEN_EOF)
			break ;
		if (!process_token(cmd, tokens_ptr, &arg_list))
		{
			free(cmd);
			ft_lstclear(&arg_list, free);
			return (NULL);
		}
	}
	cmd->argv = build_argv_from_list(arg_list);
	ft_lstclear(&arg_list, free);
	return (cmd);
}

t_pipeline	*parser(t_list *tokens, int status)
{
	t_pipeline	*pipeline;
	t_command	*cmd;
	t_list		*current_tokens;

	pipeline = pipeline_create();
	if (!pipeline || !tokens)
		return (NULL);
	current_tokens = tokens;
	while (current_tokens)
	{
		if (((t_token *)current_tokens->content)->type == TOKEN_EOF)
			break ;
		cmd = build_command(&current_tokens, status);
		if (!pipeline_add_command(pipeline, cmd))
		{
			ft_putstr_fd("Error: failed to add command to pipeline\n", 2);
			pipeline_destroy(pipeline);
			return (NULL);
		}
		if (current_tokens
			&& ((t_token *)current_tokens->content)->type == TOKEN_PIPE)
			current_tokens = current_tokens->next;
	}
	ft_lstclear(&tokens, free_token);
	return (pipeline);
}
