/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <cde-la-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 17:56:41 by cde-la-r          #+#    #+#             */
/*   Updated: 2024/09/26 15:29:03 by cde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "libft.h"

/*
** Joins two strings and frees the first string.
**
** @param s1: The first string to join.
** @param s2: The second string to join.
** @return: The newly allocated joined string.
*/
char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*result;

	if (!s1 || !s2)
		return (NULL);
	result = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (result);
}

char	*get_user(void)
{
	char	*user;

	user = getenv("USER");
	if (user == NULL)
		user = getenv("LOGNAME");
	if (user == NULL)
		return (ft_strdup("user"));
	return (ft_strdup(user));
}

char	*get_host(void)
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

char	*get_path(void)
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
