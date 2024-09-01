/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <cde-la-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 17:56:41 by cde-la-r          #+#    #+#             */
/*   Updated: 2024/08/30 17:56:41 by cde-la-r         ###   ########.fr       */
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

char	*get_user(void)
{
	char	*user;

	user = getenv("USER");
	if (user == NULL)
		user = "user";
	return (user);
}

char	*get_host(void)
{
	int		fd;
	char	hostname[256];
	ssize_t	bytes_read;

	fd = open("/proc/sys/kernel/hostname", O_RDONLY);
	if (fd < 0)
	{
		perror("minishell: open");
		return (NULL);
	}
	bytes_read = read(fd, hostname, sizeof(hostname) - 1);
	close(fd);
	if (bytes_read <= 0)
	{
		perror("minishell: read");
		return (NULL);
	}
	hostname[bytes_read] = '\0';
	if (hostname[bytes_read - 1] == '\n')
		hostname[bytes_read - 1] = '\0';
	return (ft_strdup(hostname));
}
