/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <code@cesardelarosa.xyz>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 17:51:38 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/03/31 17:15:37 by cesi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"
#include <fcntl.h>
#include <limits.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdlib.h>
#include <unistd.h>

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

static char	*shorten_cwd(const char *cwd, const char *user)
{
	size_t	ulen;

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

char	*build_prompt(char **envp)
{
	char	cwd[PATH_MAX];
	char	*user;
	char	*host;
	char	*short_cwd;
	char	*prompt;

	(void)envp;
	user = getenv("USER");
	if (!user)
		user = "unknown";
	host = get_hostname();
	if (!getcwd(cwd, sizeof(cwd)))
		ft_strlcpy(cwd, "unknown", sizeof(cwd));
	short_cwd = shorten_cwd(cwd, user);
	if (isatty(STDOUT_FILENO))
	{
		prompt = ft_strjoin_free(ft_strdup("\033[1;32m"), ft_strdup(user), 3);
		prompt = ft_strjoin_free(prompt, ft_strdup("\033[0m at \033[1;34m"), 3);
		prompt = ft_strjoin_free(prompt, ft_strdup(host), 3);
		prompt = ft_strjoin_free(prompt, ft_strdup("\033[0m in \033[1;33m"), 3);
		prompt = ft_strjoin_free(prompt, ft_strdup(short_cwd), 3);
		prompt = ft_strjoin_free(prompt, ft_strdup("\033[0m via \033[1;35mminishell\033[0m$ "), 3);
	}
	else
	{
		prompt = ft_strjoin_free(ft_strdup(user), ft_strdup(" at "), 3);
		prompt = ft_strjoin_free(prompt, ft_strdup(host), 3);
		prompt = ft_strjoin_free(prompt, ft_strdup(" in "), 3);
		prompt = ft_strjoin_free(prompt, ft_strdup(short_cwd), 3);
		prompt = ft_strjoin_free(prompt, ft_strdup("via minishell$ "), 3);
	}
	free(host);
	free(short_cwd);
	return (prompt);
}

char	*read_line(char **envp)
{
	char	*line;
	char	*prompt;
	char	*trimmed;

	(void)envp;
	while (1)
	{
		prompt = build_prompt(envp);
		line = readline(prompt);
		free(prompt);
		if (!line)
			return (NULL);
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
