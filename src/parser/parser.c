/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <code@cesardelarosa.xyz>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 18:08:20 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/06/18 00:39:06 by cesi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"
#include "struct_creation.h"
#include <stdio.h>
#include <stdlib.h>

int			parse_token(t_command *cmd, t_list **tokens_ptr, t_list **arg_lst,
				t_ctx *ctx);
t_command	*build_command(t_list **tokens_ptr, t_ctx *ctx,
				t_token_parser_ft parse_ft);

t_pipeline	*parser(t_list *tokens, t_ctx *ctx)
{
	t_pipeline	*pipeline;
	t_command	*cmd;
	t_list		*current_tokens;

	pipeline = pipeline_create(ctx);
	if (!pipeline || !tokens)
		return (NULL);
	current_tokens = tokens;
	while (current_tokens)
	{
		if (((t_token *)current_tokens->content)->type == TOKEN_EOF)
			break ;
		cmd = build_command(&current_tokens, ctx, &parse_token);
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
