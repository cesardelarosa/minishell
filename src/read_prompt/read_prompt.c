/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_prompt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <code@cesardelarosa.xyz>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 17:51:38 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/06/18 15:59:02 by cesi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <fcntl.h>
#include <limits.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdlib.h>
#include <unistd.h>

#define GREEN "\033[1;32m"
#define BLUE "\033[1;34m"
#define YELLOW "\033[1;33m"
#define MAGENTA "\033[1;35m"
#define RESET "\033[0m"
#define RED "\033[1;31m"

static char	*get_hostname(void)
{
	int		fd;
	char	buf[256];
	int		n;
	char	*host;

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

static char	*get_cwd(const char *user)
{
	char	cwd[PATH_MAX];
	size_t	ulen;

	if (!getcwd(cwd, sizeof(cwd)))
		return (ft_strdup("unknown"));
	ulen = ft_strlen(user);
	if (!ft_strncmp(cwd, "/home/", 6) && !ft_strncmp(cwd + 6, user, ulen)
		&& (cwd[6 + ulen] == '/' || cwd[6 + ulen] == '\0'))
	{
		if (cwd[6 + ulen] == '\0')
			return (ft_strdup("~"));
		else
			return (ft_strjoin("~", cwd + 6 + ulen));
	}
	return (ft_strdup(cwd));
}

static char	*build_prompt(int status)
{
	char	*user;
	char	*host;
	char	*cwd;
	char	*status_indicator;

	user = get_user();
	host = get_hostname();
	cwd = get_cwd(user);
	status_indicator = NULL;
	if (isatty(STDOUT_FILENO))
	{
		if (status != 0)
			status_indicator = ft_strdup(RED "✗ " RESET);
		return (ft_strjoin_free(ft_strjoin_free(ft_strjoin_free(ft_strjoin_free(
							ft_strjoin_free(ft_strjoin_free(ft_strjoin_free(
										status_indicator, GREEN, 1), user, 3),
								RESET " at " BLUE, 1), host, 3), RESET " in "
						YELLOW, 1), cwd, 3), RESET " via " MAGENTA "minishell"
				RESET "$ ", 1));
	}
	return (ft_strjoin_free(ft_strjoin_free(ft_strjoin_free(ft_strjoin_free(
						ft_strjoin_free(user, " at ", 1), host, 3), " in ", 1),
				cwd, 3), "via minishell$ ", 1));
}

char	*read_prompt(int status)
{
	char	*line;
	char	*prompt;
	char	*trimmed;

	while (1)
	{
		prompt = build_prompt(status);
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
