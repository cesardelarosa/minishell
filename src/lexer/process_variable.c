/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_variable.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <code@cesardelarosa.xyz>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 11:53:02 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/04/01 11:53:14 by cde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"

static int	is_valid_var_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}

static char	*read_variable(const char **s)
{
	const char	*start;
	char		*var;
	size_t		len;

	(*s)++;
	if (**s == '?')
	{
		var = ft_strdup("?");
		(*s)++;
		return (var);
	}
	start = *s;
	while (**s && is_valid_var_char(**s))
		(*s)++;
	len = *s - start;
	return (ft_substr(start, 0, len));
}

int	process_variable(char **s, t_list **tokens)
{
	t_token	*token;
	char	*value;

	value = read_variable((const char **)s);
	token = create_token(TOKEN_VARIABLE, value);
	ft_lstadd_back(tokens, ft_lstnew(token));
	return (0);
}
