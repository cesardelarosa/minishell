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

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include "minishell.h"
#include "libft.h"

/*
** Handle pipe ('|'). Redirects output of one command to input of another.
*/
void	handle_pipe(t_ast_node *node)
{
	int	pipe_fd[2];
	int	pid1;
	int	pid2;
	int	status;

	if (!node || !node->left || !node->right)
	{
		printf("minishell: missing command for pipe\n");
		return ;
	}
	if (pipe(pipe_fd) == -1)
	{
		perror("minishell: pipe error");
		return ;
	}
	pid1 = fork();
	if (pid1 == -1)
	{
		perror("minishell: fork error");
		return ;
	}
	if (pid1 == 0)
	{
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		exec(node->left);
		exit(EXIT_FAILURE);
	}
	pid2 = fork();
	if (pid2 == -1)
	{
		perror("minishell: fork error");
		return ;
	}
	if (pid2 == 0)
	{
		dup2(pipe_fd[0], STDIN_FILENO);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		exec(node->right);
		exit(EXIT_FAILURE);
	}
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	waitpid(pid1, &status, 0);
	waitpid(pid2, &status, 0);
}

void	handle_redirection(t_ast_node *node, int mode)
{
	int	fd;
	int	backup;
	int	fileno;

	if (!node || !node->right || !node->right->args || !node->right->args[0])
	{
		printf("minishell: missing file for append redirection\n");
		return ;
	}
	if (mode == O_RDONLY)
		fileno = STDIN_FILENO;
	else
		fileno = STDOUT_FILENO;
	backup = dup(fileno);
	fd = open(node->right->args[0], mode, 0644);
	if (fd == -1)
	{
		perror("minishell: open error");
		return ;
	}
	dup2(fd, fileno);
	close(fd);
	exec(node->left);
	dup2(backup, fileno);
	close(backup);
}

/*
** Handle heredoc ('<<'). Simulates the heredoc by writing input to a pipe.
*/
void	handle_heredoc(t_ast_node *node)
{
	char	*line;
	char	*delimiter;
	int		fd;

	delimiter = ft_strdup(node->right->args[0]);
	if (!delimiter)
		return ;
	fd = open("heredoc_tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("minishell: open error");
		free(delimiter);
		return ;
	}
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strncmp(line, delimiter, ft_strlen(delimiter) + 1) == 0)
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	close(fd);
	free(delimiter);
}
