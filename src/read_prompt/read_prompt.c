/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_prompt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <code@cesardelarosa.xyz>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 17:51:38 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/06/23 18:54:03 by cde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "libft.h"
#include <stdio.h>
#include <fcntl.h>
#include <limits.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdlib.h>
#include <unistd.h>

#define GREEN "\001\033[1;32m\002" 
#define BLUE "\001\033[1;34m\002"
#define YELLOW "\001\033[1;33m\002"
#define MAGENTA "\001\033[1;35m\002"
#define RESET  "\001\033[0m\002"
#define RED "\001\033[1;31m\002"

static char	*get_hostname(void)
{
	int		fd;
	char	buf[256];
	int		n;
	char	*host;
	char	*dot;

	fd = open("/etc/hostname", O_RDONLY);
	if (fd < 0)
		return (ft_strdup("unknown"));
	n = read(fd, buf, 255);
	if (n <= 0)
	{
		close(fd);
		return (ft_strdup("unknown"));
	}
	buf[n] = '\0';
	close(fd);
	host = ft_strtrim(buf, "\n");
	if (!host)
		return (ft_strdup("unknown"));
	dot = ft_strchr(host, '.');
	if (dot)
		*dot = '\0';
	return (host);
}

static char	*get_user(void)
{
	char	*user;

	user = getenv("USER");
	if (!user)
		return (ft_strdup("unknown"));
	return (ft_strdup(user));
}

char	*get_cwd(t_env *env)
{
	char		*pwd_path;
	char		*home_path;
	size_t		home_len;

	pwd_path = env_get(env, "PWD");
	home_path = env_get(env, "HOME");
	if (!pwd_path)
		return (ft_strdup(""));
	if (home_path)
	{
		home_len = ft_strlen(home_path);
		if (ft_strcmp(pwd_path, home_path) == 0)
			return (ft_strdup("~"));
		if (ft_strncmp(pwd_path, home_path, home_len) == 0
			&& pwd_path[home_len] == '/')
			return (ft_strjoin("~", pwd_path + home_len));
	}
	return (ft_strdup(pwd_path));
}

static char	*build_prompt(t_ctx *ctx)
{
	char	*user;
	char	*host;
	char	*cwd;
	char	*error;

	user = get_user();
	host = get_hostname();
	cwd = get_cwd(ctx->env);
	error = NULL;
	if (!isatty(STDOUT_FILENO))
		return (ft_strjoin_free(ft_strjoin_free(ft_strjoin_free(ft_strjoin_free(
							ft_strjoin_free(ft_strjoin_free(ft_strjoin_free(
										ft_strjoin_free("(", ctx->prog_name, 1),
										") ", 1), user, 3), "@", 1), host, 3),
						":", 1), cwd, 3), "$ ", 1));
	if (ctx->status != 0)
		error = ft_strdup(RED "✗ " RESET);
	return (ft_strjoin_free(ft_strjoin_free(ft_strjoin_free(ft_strjoin_free(
						ft_strjoin_free(ft_strjoin_free(ft_strjoin_free(
									ft_strjoin_free(ft_strjoin_free(
											ft_strjoin_free("(" MAGENTA,
												ctx->prog_name, 0), RESET ") ",
											1), error, 3), GREEN, 1),
								user, 3), RESET "@" BLUE, 1), host, 3), RESET
					":" YELLOW, 1), cwd, 3), RESET "$ ", 1));
}

char	*read_prompt(t_ctx *ctx)
{
	char	*line;
	char	*prompt;
	char	*trimmed;

	while (1)
	{
		prompt = build_prompt(ctx);
		line = readline(prompt);
		free(prompt);
		if (!line)
		{
			rl_clear_history();
			return (NULL);
		}
		trimmed = ft_strtrim(line, " \t\n");
		free(line);
		if (trimmed && *trimmed)
		{
			add_history(trimmed);
			return (trimmed);
		}
		free(trimmed);
	}
}
