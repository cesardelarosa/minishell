/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <cde-la-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 17:56:41 by cde-la-r          #+#    #+#             */
/*   Updated: 2024/09/19 14:06:42 by cde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "libft.h"

char	*ft_strjoin_free(char *s1, const char *s2)
{
	char	*result;

	if (!s1 || !s2)
		return (NULL);
	result = ft_strjoin(s1, s2);
	free(s1);
	return (result);
}

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

char	*get_user(void)
{
	char	*user;

	user = getenv("USER");
	if (user == NULL)
		return ("user");
	return (user);
}

char	*get_host(void)
{
	char	*host;
	int		i;

	host = getenv("HOSTNAME");
	if (host == NULL)
		return ("host");
	i = -1;
	while (host[++i])
	{
		if (host[i] == '.')
			host[i] = '\0';
	}
	return (host);
}
