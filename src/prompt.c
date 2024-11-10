/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <cde-la-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 17:56:41 by cde-la-r          #+#    #+#             */
/*   Updated: 2024/10/13 13:52:12 by cde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <term.h>
#include <fcntl.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft.h"
#include "minishell.h"
#include "colors.h"

static char	*get_user(void)
{
	char	*user;

	user = getenv("USER");
	if (user == NULL)
		user = getenv("LOGNAME");
	if (user == NULL)
		return (ft_strdup("user"));
	return (ft_strdup(user));
}

static char	*get_host(void)
{
	char	hostname[256];
	int		fd;
	ssize_t	len;

	fd = open("/etc/hostname", O_RDONLY);
	if (fd == -1)
		return (ft_strdup("host"));
	len = read(fd, hostname, sizeof(hostname) - 1);
	if (len <= 0)
	{
		close(fd);
		return (ft_strdup("host"));
	}
	hostname[len] = '\0';
	close(fd);
	len = 0;
	while (hostname[len++])
	{
		if (hostname[len] == '.' || hostname[len] == '\n')
		{
			hostname[len] = '\0';
			break ;
		}
	}
	return (ft_strdup(hostname));
}

static char	*get_path(void)
{
	char	cwd[1024];
	char	*home;

	if (getcwd(cwd, sizeof(cwd)) == NULL)
		return (ft_strdup("path"));
	home = getenv("HOME");
	if (home && ft_strncmp(cwd, home, ft_strlen(home)) == 0)
		return (ft_strjoin("~", cwd + ft_strlen(home)));
	return (ft_strdup(cwd));
}

void	print_prompt(void)
{
	char	*term;
	char	*user;
	char	*host;
	char	*path;

	term = getenv("TERM");
	user = get_user();
	host = get_host();
	path = get_path();
	if (term != NULL && (tgetent(NULL, term) > 0 && tgetnum("colors") >= 0))
	{
		printf(TEXT_CYAN"%s"TEXT_WHITE" at "TEXT_YELLOW"%s"TEXT_WHITE" in "
			TEXT_GREEN"%s"RESET_COLOR"$ ", user, host, path);
	}
	else
		printf("%s at %s in %s$ ", user, host, path);
	free(user);
	free(host);
	free(path);
}

char	*read_input(void)
{
	char	*input;

	if (g_exit_status != 130)
	{
		rl_replace_line("", 0);
		print_prompt();
		input = readline("");
	}
	else
		input = readline("");
	if (input == NULL)
		exit(0);
	if (*input == '\0')
	{
		free(input);
		g_exit_status = 0;
		return (NULL);
	}
	else
		add_history(input);
	return (input);
}
