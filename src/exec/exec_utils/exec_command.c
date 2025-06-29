/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <code@cesardelarosa.xyz>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 12:15:14 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/06/22 22:59:54 by cde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errors.h"
#include "common.h"
#include "execution.h"
#include "builtin.h"

static char	*get_env_value(char *key, char **envp)
{
	size_t	len;

	if (!envp || !*envp)
		return (NULL);
	len = ft_strlen(key);
	while (*envp)
	{
		if (ft_strncmp(*envp, key, len) == 0 && (*envp)[len] == '=')
			return (*envp + len + 1);
		envp++;
	}
	return (NULL);
}

static char	*search_in_path(char *cmd, char **paths)
{
	char	*full_path;
	int		i;

	i = 0;
	while (paths[i])
	{
		full_path = ft_strjoin_free(ft_strjoin(paths[i], "/"), cmd, 1);
		if (!full_path)
			return (NULL);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}

static char	*find_executable(char *cmd, char **envp)
{
	char	**paths;
	char	*path_env;
	char	*exec_path;

	if (!cmd || !*cmd)
		return (NULL);
	if (ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	path_env = get_env_value("PATH", envp);
	if (!path_env)
		return (ft_strjoin("./", cmd));
	paths = ft_split(path_env, ':');
	exec_path = search_in_path(cmd, paths);
	ft_free_split(paths);
	return (exec_path);
}

void	execute_command(t_command *cmd)
{
	char			*path;
	t_builtin_ft	builtin_ft;
	int				redir_status;

	redir_status = handle_redirs(cmd->redirs);
	if (redir_status == 130)
		error_exit_code(redir_status, NULL, NULL, cmd->p);
	if (redir_status != 0)
		error_exit_code(1, "redirection failed", NULL, cmd->p);
	builtin_ft = get_builtin_ft(cmd->argv[0]);
	if (builtin_ft)
		error_exit_code(builtin_ft(cmd->argv, cmd->p->ctx->env),
			NULL, NULL, cmd->p);
	path = find_executable(cmd->argv[0], cmd->p->ctx->env->envp);
	if (!path)
		error_exit_code(127, "Command not found", cmd->argv[0], cmd->p);
	execve(path, cmd->argv, cmd->p->ctx->env->envp);
	free(path);
	if (errno == ENOENT)
		error_exit_code(127, "Command not found", cmd->argv[0], cmd->p);
	if (errno == EACCES)
		error_exit_code(126, "Permission denied", cmd->argv[0], cmd->p);
	error_exit_code(126, strerror(errno), cmd->argv[0], cmd->p);
}
