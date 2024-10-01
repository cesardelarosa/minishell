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
#include "libft.h"

/*
** Joins two strings and frees the first string.
**
** @param s1: The first string to join.
** @param s2: The second string to join.
** @return: The newly allocated joined string.
*/
char	*ft_strjoin_free(char *s1, const char *s2)
{
	char	*result;

	if (!s1 || !s2)
		return (NULL);
	result = ft_strjoin(s1, s2);
	if (s1)
		free(s1);
	return (result);
}

/*
** Gets the current working directory, replacing the home path with '~'.
**
** @return: The current path as a string.
*/
char	*get_path(void)
{
	char	*path;
	char	*home;
	size_t	home_len;

	path = getenv("PWD");
	if (path == NULL)
		return ("path");
	home = getenv("HOME");
	home_len = ft_strlen(home);
	if (home && ft_strncmp(path, home, home_len) == 0)
	{
		ft_memmove(path + 1, path + home_len, ft_strlen(path) + 1);
		path[0] = '~';
	}
	return (path);
}

/*
** Gets the username from the environment variables.
**
** @return: The username as a string.
*/
char	*get_user(void)
{
	char	*user;

	user = getenv("USER");
	if (user == NULL)
		return ("user");
	return (user);
}

/*
** Gets the hostname from the environment variables, truncating at the first dot.
**
** @return: The hostname as a string.
*/
char	*get_host(void)
{
	char	*host;
	int		i;

	host = getenv("NAME");
	if (host == NULL)
		return ("host");
	i = 0;
	while (host[i])
	{
		if (host[i] == '.')
			host[i] = '\0';
		i++;
	}
	return (host);
}
