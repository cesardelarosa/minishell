/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <code@cesardelarosa.xyz>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 18:08:20 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/03/29 18:10:41 by cde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "struct_creation.h"
#include <stdio.h>
#include <stdlib.h>
#include "lexer.h"

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

static t_command	*build_command(t_list **tokens_ptr)
{
	t_command		*cmd;
	t_list			*arg_list;
	t_token			*token;
	t_token_type	op_type;

	cmd = ft_calloc(1, sizeof(t_command));
	if (!cmd)
		return (NULL);
	arg_list = NULL;
	while (*tokens_ptr)
	{
		token = (t_token *)((*tokens_ptr)->content);
		if (token->type == TOKEN_PIPE || token->type == TOKEN_EOF)
			break ;
		if (token->type == TOKEN_REDIRECT_IN
			|| token->type == TOKEN_REDIRECT_OUT || token->type == TOKEN_HEREDOC
			|| token->type == TOKEN_APPEND)
		{
			op_type = token->type;
			*tokens_ptr = (*tokens_ptr)->next;
			if (!*tokens_ptr)
			{
				ft_putstr_fd("Error: redirection operator without target\n", 2);
				free(cmd);
				return (NULL);
			}
			token = (t_token *)((*tokens_ptr)->content);
			if (token->type != TOKEN_WORD && token->type != TOKEN_VARIABLE
				&& token->type != TOKEN_SINGLE_QUOTED_STRING
				&& token->type != TOKEN_DOUBLE_QUOTED_STRING)
			{
				ft_putstr_fd("Error: redirection target must be a word\n", 2);
				free(cmd);
				return (NULL);
			}
			if (op_type == TOKEN_REDIRECT_IN)
				command_add_redir(cmd, REDIR_INPUT, token->value);
			else if (op_type == TOKEN_REDIRECT_OUT)
				command_add_redir(cmd, REDIR_OUTPUT, token->value);
			else if (op_type == TOKEN_HEREDOC)
				command_add_redir(cmd, REDIR_HEREDOC, token->value);
			else if (op_type == TOKEN_APPEND)
				command_add_redir(cmd, REDIR_APPEND, token->value);
			*tokens_ptr = (*tokens_ptr)->next;
		}
		else if (token->type == TOKEN_WORD || token->type == TOKEN_VARIABLE
			|| token->type == TOKEN_SINGLE_QUOTED_STRING
			|| token->type == TOKEN_DOUBLE_QUOTED_STRING)
		{
			ft_lstadd_back(&arg_list, ft_lstnew(ft_strdup(token->value)));
			*tokens_ptr = (*tokens_ptr)->next;
		}
		else if (token->type == TOKEN_ERROR)
		{
			ft_putstr_fd("Error: ", 2);
			ft_putstr_fd(token->value, 2);
			ft_putstr_fd("\n", 2);
			free(cmd);
			ft_lstclear(&arg_list, free);
			return (NULL);
		}
		else
			*tokens_ptr = (*tokens_ptr)->next;
	}
	cmd->argv = build_argv_from_list(arg_list);
	ft_lstclear(&arg_list, free);
	return (cmd);
}

t_pipeline	*parse_tokens(t_list *tokens)
{
	t_pipeline	*pipeline;
	t_command	*cmd;
	t_list		*current_tokens;

	pipeline = pipeline_create();
	if (!pipeline)
		return (NULL);
	current_tokens = tokens;
	while (current_tokens)
	{
		if (((t_token *)current_tokens->content)->type == TOKEN_EOF)
			break ;
		cmd = build_command(&current_tokens);
		if (!cmd)
		{
			ft_putstr_fd("Error: failed to build command from tokens\n", 2);
			pipeline_destroy(pipeline);
			return (NULL);
		}
		if (!pipeline_add_command(pipeline, cmd))
		{
			ft_putstr_fd("Error: failed to add command to pipeline\n", 2);
			command_destroy(cmd);
			pipeline_destroy(pipeline);
			return (NULL);
		}
		if (current_tokens
			&& ((t_token *)current_tokens->content)->type == TOKEN_PIPE)
			current_tokens = current_tokens->next;
	}
	return (pipeline);
}

void	free_tokens(t_list *tokens)
{
	ft_lstclear(&tokens, free_token);
}
