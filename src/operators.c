/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operators.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <cde-la-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 10:13:31 by cde-la-r          #+#    #+#             */
/*   Updated: 2024/10/03 10:13:36 by cde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/wait.h>
#include "libft.h"
#include "minishell.h"

void	fork_and_exec(t_operator op, int *pipe_fd, int is_right)
{
	pid_t	pid;
	int		fileno;

	if (is_right)
		fileno = STDIN_FILENO;
	else
		fileno = STDOUT_FILENO;
	pid = fork();
	if (pid == -1)
	{
		perror("minishell: fork error");
		return ;
	}
	if (pid == 0)
	{
		dup2(pipe_fd[!is_right], fileno);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		if (is_right)
			exec(op.right);
		else
			exec(op.left);
		exit(EXIT_FAILURE);
	}
}

void	handle_pipe(t_operator op)
{
	int	pipe_fd[2];
	int	status;

	if (!op.left || !op.right)
	{
		fprintf(stderr, "minishell: missing command for pipe\n");
		return ;
	}
	if (pipe(pipe_fd) == -1)
	{
		perror("minishell: pipe error");
		return ;
	}
	fork_and_exec(op, pipe_fd, 0);
	fork_and_exec(op, pipe_fd, 1);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	waitpid(-1, &status, 0);
	waitpid(-1, &status, 0);
}

int	handle_redirection(t_file *file, const char *filename, int flags)
{
	if (file->fd != -1)
		close(file->fd);
	file->fd = open(filename, flags, 0644);
	if (file->fd < 0)
	{
		perror("Error opening file");
		return (-1);
	}
	if (file->file != NULL)
		free(file->file);
	file->file = ft_strdup(filename);
	return (0);
}

static int	write_to_heredoc(int write_fd, const char *delimiter)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (line == NULL || ft_strcmp(line, (char *)delimiter) == 0)
		{
			free(line);
			break ;
		}
		write(write_fd, line, ft_strlen(line));
		write(write_fd, "\n", 1);
		free(line);
	}
	return (0);
}

int	handle_heredoc(t_file *input, const char *delimiter)
{
	int	fd[2];

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
	input->file = ft_strdup((char *)delimiter);
	write_to_heredoc(fd[1], delimiter);
	close(fd[1]);
	return (0);
}
