/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <cde-la-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 13:45:46 by cde-la-r          #+#    #+#             */
/*   Updated: 2024/10/01 17:43:04 by cde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "libft.h"
#include "minishell.h"
#include "builtins.h"
#include "operators.h"
#include "operators_bonus.h"

extern char	**environ;

/*
** Searches for the full path of a command by checking each directory
** in the PATH environment variable. If found, returns the full path.
** Otherwise, returns NULL.
**
** @param cmd: The command to search for in the PATH directories.
** @return: The full path of the command if found, NULL otherwise.
*/
char	*which(const char *cmd)
{
	char	*path;
	char	*dir;
	char	*full_path;
	size_t	cmd_len;

	path = getenv("PATH");
	cmd_len = ft_strlen(cmd);
	while (path && *path)
	{
		dir = (char *)path;
		while (*path && *path != ':')
			path++;
		full_path = (char *)malloc((path - dir) + cmd_len + 2);
		if (full_path == NULL)
			return (NULL);
		ft_memcpy(full_path, dir, path - dir);
		full_path[path - dir] = '/';
		ft_memcpy(full_path + (path - dir) + 1, cmd, cmd_len);
		full_path[(path - dir) + cmd_len + 1] = '\0';
		if (access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
		path += *path != '\0';
	}
	return (NULL);
}

/*
** Handles the execution of external commands. If the command is found,
** it runs execve. If not, it tries to find the command using 'which'.
**
** @param args: Command and arguments to execute.
*/
void	handle_extern(char **args)
{
	char	*exec_path;

	if (access(args[0], X_OK) == 0)
		execve(args[0], args, environ);
	else if (access(args[0], F_OK) != 0)
	{
		exec_path = which(args[0]);
		if (exec_path != NULL)
		{
			execve(exec_path, args, environ);
			free(exec_path);
		}
		else
			perror("minishell: command not found");
	}
	else
		perror("minishell: execution failed");
	exit(EXIT_FAILURE);
}

/*
** Checks if the command is a built-in. If it is, it calls the corresponding
** function. Returns 1 if the command is a built-in, 0 otherwise.
**
** @param args: The arguments of the command to check.
** @return: 1 if the command is a built-in, 0 otherwise.
*/
int	handle_builtin(char **args)
{
	if (!ft_strncmp(args[0], "cd", 3))
		builtin_cd(args);
	else if (!ft_strncmp(args[0], "pwd", 4))
		builtin_pwd();
	else if (!ft_strncmp(args[0], "echo", 5))
		builtin_echo(args);
	else if (!ft_strncmp(args[0], "exit", 5))
		builtin_exit(args);
	else
		return (0);
	return (1);
}

/*
** Handles the execution of a single command. If the command is not a built-in,
** it forks a new process to execute the external command.
**
** @param node: The AST node representing the command to execute.
*/
void	handle_command(t_ast_node *node)
{
	pid_t	pid;
	int		status;

	if (node == NULL || node->args == NULL)
		return ;
	if (node->args[0] != NULL && handle_builtin(node->args) == 0)
	{
		pid = fork();
		if (pid == 0)
			handle_extern(node->args);
		else if (pid < 0)
			perror("minishell: fork error");
		else
		{
			if (waitpid(pid, &status, 0) == -1)
				perror("minishell: waitpid error");
			if (WIFEXITED(status))
				g_exit_status = WEXITSTATUS(status);
		}
	}
}

/*
** Recursively executes the AST tree. It checks if the current node is a command
** and handles it. Then it continues to the left and right nodes.
**
** @param root: The root node of the AST to execute.
*/
void	exec(t_ast_node *root)
{
//	print_node(root);	//DEBUGGIN UTILITY
	if (root == NULL)
		return ;
	if (root->type == NODE_COMMAND)
		handle_command(root);
	else if (root->type == NODE_PIPE)
		handle_pipe(root);
	else if (root->type == NODE_REDIRECTION_IN)
		handle_redirection_in(root);
	else if (root->type == NODE_REDIRECTION_OUT)
		handle_redirection_out(root);
	else if (root->type == NODE_REDIRECTION_APPEND)
		handle_redirection_append(root);
	else if (root->type == NODE_HEREDOC)
		handle_heredoc(root);
	else if (root->type == NODE_AND)
		handle_and(root);
	else if (root->type == NODE_OR)
		handle_or(root);
	else
		printf("minishell: unsupported node type\n");
}
