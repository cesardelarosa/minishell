/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <cde-la-r@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 04:50:34 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/02/18 13:40:36 by cde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 4242
#endif

#ifndef OPEN_MAX
# define OPEN_MAX 1024
#endif

char	*read_line(char *line, int fd)
{
	char	buffer[BUFFER_SIZE + 1];
	ssize_t	nbytes;
	char	*tmp;

	while (!ft_strchr(line, '\n'))
	{
		nbytes = read(fd, buffer, BUFFER_SIZE);
		if (nbytes == 0)
			break ;
		if (nbytes == -1)
		{
			free(line);
			return (NULL);
		}
		buffer[nbytes] = '\0';
		tmp = ft_strjoin(line, buffer);
		free(line);
		line = tmp;
	}
	return (line);
}

char	*save_tail(char *line)
{
	char	*next;
	char	*tail;

	next = ft_strchr(line, '\n');
	if (!next)
		return (NULL);
	tail = ft_strdup(next + 1);
	*next = '\0';
	if (tail[0] == '\0')
	{
		free(tail);
		return (NULL);
	}
	return (tail);
}

char	*get_next_line(int fd)
{
	static char	*tail[OPEN_MAX];
	char		*line;

	if (fd < 0 || fd >= OPEN_MAX)
		return (NULL);
	if (!tail[fd])
		tail[fd] = ft_strdup("");
	line = read_line(tail[fd], fd);
	tail[fd] = save_tail(line);
	return (line);
}
