/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <code@cesardelarosa.xyz>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 12:27:40 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/06/24 13:06:05 by cde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "env.h"
#include "libft.h"
#include <readline/readline.h>
#include <stdio.h>
#include <stdbool.h>
#include "signals.h"

#define EOF_MSG "minishell: warning: here-document delimited by end-of-file\n"

extern volatile sig_atomic_t	g_sigint_received;

static char	*append_line_to_buffer(char *buffer, char *line)
{
	char	*with_newline;
	char	*new_buffer;

	with_newline = ft_strjoin(line, "\n");
	if (!with_newline)
	{
		free(buffer);
		return (NULL);
	}
	new_buffer = ft_strjoin(buffer, with_newline);
	free(with_newline);
	free(buffer);
	return (new_buffer);
}

char	*read_heredoc_input(char *delimiter, bool expand_vars, t_ctx *ctx)
{
	char	*line;
	char	*buffer;
	char	*processed_line;

	buffer = ft_strdup("");
	if (!buffer)
		return (NULL);
	g_sigint_received = 0;
	while (g_sigint_received == 0)
	{
		line = readline("> ");
		if (!line || g_sigint_received)
		{
			if (!line && !g_sigint_received)
				ft_putstr_fd(EOF_MSG, 2);
			free(line);
			break ;
		}
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		processed_line = line;
		if (expand_vars)
		{
			processed_line = env_expand_variables(line, ctx->env);
			free(line);
			if (!processed_line)
			{
				free(buffer);
				return (NULL);
			}
		}
		buffer = append_line_to_buffer(buffer, processed_line);
		if (expand_vars)
			free(processed_line);
		if (!buffer)
			return (NULL);
	}
	if (g_sigint_received)
	{
		free(buffer);
		return (NULL);
	}
	return (buffer);
}
