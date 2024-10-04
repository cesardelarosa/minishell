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

void	handle_heredoc(t_ast_node *node)
{
	char	*line;
	int		pipefd[2];
	int		status;
	pid_t	pid;

	if (!node->delimiter)
		return ;
	if (pipe(pipefd) == -1)
	{
		perror("minishell: pipe error");
		return ;
	}
	pid = fork();
	if (pid == -1)
	{
		perror("minishell: fork error");
		return ;
	}
	if (pid == 0)
	{
		while (1)
		{
			line = readline("> ");
			if (!line)
			{
				close(pipefd[1]);
				break ;
			}
			if (ft_strncmp(line, node->delimiter, ft_strlen(node->delimiter) + 1) == 0)
			{
				free(line);
				close(pipefd[1]);
				break ;
			}
			write(pipefd[1], line, ft_strlen(line));
			write(pipefd[1], "\n", 1);
			free(line);
		}
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
		exec(node->left);
		exit(0);
	}
	else
	{
		close(pipefd[0]);
		close(pipefd[1]);
		waitpid(pid, &status, 0);
	}
}
