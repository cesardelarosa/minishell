/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globbing_utils_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <code@cesardelarosa.xyz>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 08:32:29 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/06/25 01:24:55 by cde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_glob_bonus.h"
#include "libft.h"
#include <stddef.h>
#include <sys/stat.h>
#include <stdlib.h>

int	add_match(char ***results, size_t *res_count, size_t *res_capacity,
		char *new_path)
{
	char	**temp;
	size_t	old_bytes;

	if (*res_count >= *res_capacity)
	{
		old_bytes = sizeof(char *) * (*res_capacity);
		*res_capacity *= 2;
		temp = ft_realloc(*results, old_bytes, sizeof(char *)
				* (*res_capacity));
		if (!temp)
			return (0);
		*results = temp;
	}
	(*results)[*res_count] = new_path;
	(*res_count)++;
	return (1);
}

int	init_matches(char ***matches, size_t *capacity)
{
	*capacity = 10;
	*matches = malloc(sizeof(char *) * (*capacity));
	return (*matches != NULL);
}

int	is_directory(const char *path)
{
	struct stat	st;

	return (stat(path, &st) == 0 && ((st.st_mode & S_IFMT) == S_IFDIR));
}

void	bubble_sort(char **arr, size_t count)
{
	char	*temp;
	size_t	i;
	size_t	j;

	i = 0;
	while (i < count)
	{
		j = 0;
		while (j < count - i - 1)
		{
			if (ft_strcmp(arr[j], arr[j + 1]) > 0)
			{
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}

char	*join_path(const char *base, const char *name)
{
	char	*temp;
	char	*res;

	temp = ft_strjoin(base, "/");
	if (!temp)
		return (NULL);
	res = ft_strjoin(temp, name);
	free(temp);
	return (res);
}
