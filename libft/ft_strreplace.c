#include <stdlib.h>
#include "libft.h"

char	*ft_strreplace(char *str, char *start, char *end, char *replacement)
{
	char	*new_str;
	size_t	len;
	size_t	rep_len;
	size_t	new_len;

	len = ft_strlen(str);
	rep_len = ft_strlen(replacement);
	new_len = len - (end - start) + rep_len;
	new_str = (char *)malloc(new_len + 1);
	if (new_str == NULL)
		return (NULL);
	ft_memcpy(new_str, str, start - str);
	ft_memcpy(new_str + (start - str), replacement, rep_len);
	ft_memcpy(new_str + (start - str) + rep_len, end, len - (end - str));
	new_str[new_len] = '\0';
	free(str);
	return (new_str);
}
