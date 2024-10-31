/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operators.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <cde-la-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 16:42:48 by cde-la-r          #+#    #+#             */
/*   Updated: 2024/10/30 20:23:23 by cde-la-r         ###   ########.fr       */
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

void	handle_pipe(t_operator op)
{
	int		fd[2];
	pid_t	pid_left;
	pid_t	pid_right;

	if (pipe(fd) == -1)
	{
		perror("pipe failed");
		return ;
	}
	pid_left = fork();
	if (pid_left == -1)
	{
		perror("fork failed");
		return ;
	}
	if (pid_left == 0)
	{
		close(fd[0]);
		if (dup2(fd[1], STDOUT_FILENO) == -1)
			exit(EXIT_FAILURE);
		close(fd[1]);
		exec(op.left);
		exit(g_exit_status);
	}
	pid_right = fork();
	if (pid_right == -1)
	{
		perror("fork failed");
		return ;
	}
	if (pid_right == 0)
	{
		close(fd[1]);
		if (dup2(fd[0], STDIN_FILENO) == -1)
			exit(EXIT_FAILURE);
		close(fd[0]);
		exec(op.right);
		exit(g_exit_status);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(pid_left, NULL, 0);
	waitpid(pid_right, NULL, 0);
}

void	handle_and(t_operator op)
{
	exec(op.left);
	if (g_exit_status == 0)
		exec(op.right);
}

void	handle_or(t_operator op)
{
	exec(op.left);
	if (g_exit_status != 0)
		exec(op.right);
}

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
