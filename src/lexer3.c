/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrian <adrian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 09:16:24 by adrian            #+#    #+#             */
/*   Updated: 2024/11/07 09:23:14 by adrian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

void	skip_coma(char *input, int *i)
{
	char	quote_char;

	quote_char = input[*i];
	(*i)++;
	while (input[*i] && input[*i] != quote_char)
		(*i)++;
	if (!input[*i])
	{
		perror("minishell: syntax error: unclosed quotes");
		g_exit_status = 1;
		return ;
	}
	(*i)++;
}

void	add_comand(char ***tokens, char *comand, int *args)
{
	if (*args == 0)
		*tokens = malloc(sizeof(char *));
	else
		*tokens = realloc(*tokens, sizeof(char *) * (*args + 1));
	if (!*tokens)
	{
		perror("minishell: memory allocation error");
		exit(EXIT_FAILURE);
	}
	(*tokens)[*args] = comand;
	(*args)++;
}

static char	*handle_metachar(char *input, int *i)
{
	char	*result;
	int		start;
	int		len;

	start = *i;
	len = 1;
	(*i)++;
	if (input[*i - 1] == input[*i] && ft_ismetachar(input[*i]))
	{
		len++;
		(*i)++;
	}
	result = malloc(len + 1);
	if (!result)
	{
		perror("minishell: memory allocation error");
		exit(EXIT_FAILURE);
	}
	ft_strlcpy(result, input + start, len + 1);
	while (input[*i] == ' ' && input[*i])
		(*i)++;
	return (result);
}

char	*parser_word(char *input, int *i, int len)
{
	char	*result;
	int		start;

	start = *i;
	if (ft_ismetachar(input[*i]))
		return (handle_metachar(input, i));
	while (input[*i] && !ft_ismetachar(input[*i]) && input[*i] != ' ')
	{
		if (ft_isquote(input[*i]))
			skip_coma(input, i);
		else
			(*i)++;
	}
	len = *i - start;
	result = malloc(len + 1);
	if (!result)
	{
		perror("minishell: memory allocation error");
		exit(EXIT_FAILURE);
	}
	ft_strlcpy(result, input + start, len + 1);
	while (input[*i] == ' ' && input[*i])
		(*i)++;
	return (result);
}

char	**parser_comand(char *input, int *i)
{
	char	**tokens;
	char	*comand;
	int		args;

	args = 0;
	tokens = NULL;
	while (input[*i])
	{
		while (input[*i] == ' ')
			(*i)++;
		if (input[*i] == '\0')
			break ;
		comand = parser_word(input, i, 0);
		if (comand)
			add_comand(&tokens, comand, &args);
	}
	if (args > 0)
	{
		tokens = realloc(tokens, sizeof(char *) * (args + 1));
		if (!tokens)
			perror("minishell: memory allocation error");
		tokens[args] = NULL;
	}
	return (tokens);
}
