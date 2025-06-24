/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <code@cesardelarosa.xyz>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 12:27:40 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/06/25 01:00:49 by cde-la-r         ###   ########.fr       */
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

static int	process_and_append(char *line, char **buffer,
	bool expand, t_ctx *ctx)
{
	char	*processed_line;

	if (expand)
	{
		processed_line = env_expand_variables(line, ctx->env);
		free(line);
	}
	else
		processed_line = line;
	if (!processed_line)
	{
		free(*buffer);
		return (-1);
	}
	*buffer = append_line_to_buffer(*buffer, processed_line);
	free(processed_line);
	if (!*buffer)
		return (-1);
	return (1);
}

char	*read_heredoc_input(char *delimiter, bool expand_vars, t_ctx *ctx)
{
	char	*line;
	char	*buffer;

	buffer = ft_strdup("");
	if (!buffer)
		return (NULL);
	while (true)
	{
		line = readline("> ");
		if (g_sigint_received)
			return (free(line), free(buffer), NULL);
		if (!line)
		{
			ft_putstr_fd(EOF_MSG, 2);
			break ;
		}
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		if (process_and_append(line, &buffer, expand_vars, ctx) == -1)
			return (NULL);
	}
	return (buffer);
}
