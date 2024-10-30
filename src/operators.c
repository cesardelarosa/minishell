/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operators.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <cde-la-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 16:42:48 by cde-la-r          #+#    #+#             */
/*   Updated: 2024/10/30 13:09:24 by cde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft.h"
#include "minishell.h"

int	handle_redir_in(t_file *input, const char *filename)
{
	if (input->fd != -1)
		close(input->fd);
	input->fd = open(filename, O_RDONLY);
	if (input->fd < 0)
	{
		perror("Error opening file");
		return (-1);
	}
	if (input->file != NULL)
		free(input->file);
	input->file = ft_strdup(filename);
	return (0);
}

int	handle_redir_out(t_file *output, const char *filename, int type)
{
	if (output->fd != -1)
		close(output->fd);
	output->fd = open(filename, O_WRONLY | O_CREAT | type, 0644);
	if (output->fd < 0)
	{
		perror("Error opening file");
		return (-1);
	}
	if (output->file != NULL)
		free(output->file);
	output->file = ft_strdup(filename);
	return (0);
}

int	handle_heredoc(t_file *input, const char *delimiter)
{
	int		fd[2];
	char	*line;

	if (pipe(fd) == -1)
	{
		perror("Error creating pipe");
		return (-1);
	}
	if (input->fd != -1)
		close(input->fd);
	input->fd = fd[0];
	if (input->file != NULL)
		free(input->file);
	input->file = ft_strdup(delimiter);
	while (1)
	{
		line = readline("> ");
		if (line == NULL || ft_strcmp(line, (char *)delimiter) == 0)
		{
			free(line);
			break ;
		}
		write(fd[1], line, ft_strlen(line));
		write(fd[1], "\n", 1);
		free(line);
	}
	close(fd[1]);
	return (0);
}
