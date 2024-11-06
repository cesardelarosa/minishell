/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrian <adrian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 13:39:56 by cde-la-r          #+#    #+#             */
/*   Updated: 2024/11/06 22:50:56 by adrian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <stdio.h>

int	is_quotes(char c)
{
	return (c == '\'' || c == '\"');
}

/*
** Checks if all quotes in the input string are properly closed.
** Returns 1 if all are closed, otherwise returns 0.
**
** @param str: The string to check for closed quotes.
** @return: 1 if quotes are closed, 0 otherwise.
*/
int	are_quotes_closed(const char *str)
{
	int		i;
	char	quote_char;

	i = 0;
	if (str == NULL)
	{
		fprintf(stderr, "Error: Null string\n");
		return (0);
	}
	while (str[i])
	{
		if (is_quotes(str[i]))
		{
			quote_char = str[i];
			i++;
			while (str[i] && str[i] != quote_char)
				i++;
			if (str[i] == '\0')
				return (0);
			i++;
		}
		else
			i++;
	}
	return (1);
}
/*
** The lexer function splits the input string into an array of tokens.
** It uses whitespace (' ') as the delimiter. After tokenization,
** the input string is freed since it's no longer needed.
**
** @param input: The input string to be tokenized.
** @return: A NULL-terminated array of strings (tokens).
*/

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

int	is_special_char(char c)
{
	return (c == '>' || c == '<' || c == '|');
}

char	*parser_word(char *input, int *i, int len)
{
	char	*result;
	int		start;

	start = *i;
	while (input[*i] && !is_special_char(input[*i]) && input[*i] != ' ')
	{
		if (is_quotes(input[*i]))
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

char	**parser_comand(char *input, int *i)
{
	char	**tokens;
	char	*comand;
	int		args;

	args = 0;
	tokens = NULL;
	comand = parser_word(input, i, 0);
	if (comand)
		add_comand(&tokens, comand, &args);
	while (input[*i] && !is_special_char(input[*i]))
	{
		comand = parser_word(input, i, 0);
		if (comand)
			add_comand(&tokens, comand, &args);
	}
	tokens = realloc(tokens, sizeof(char *) * (args + 1));
	tokens[args] = NULL;
	return (tokens);
}

int	calc_len_new_str(char *str)
{
	char	quote_char;
	int		i;
	int		len;

	i = 0;
	len = 0;
	while (str[i])
	{
		if (is_quotes(str[i]))
		{
			quote_char = str[i];
			i++;
			while (str[i] && str[i] != quote_char)
			{
				len++;
				i++;
			}
		}
		else
			len++;
		i++;
	}
	return (len);
}

int	handle_unclosed_quotes(char **str, char *new_str)
{
	free(new_str);
	free(*str);
	*str = NULL;
	g_exit_status = 1;
	return (1);
}
/*
int	copy_within_quotes(char *str, int *i, char c, char *new_str, int *j)
{
	while (str[*i] && str[*i] != c)
		new_str[(*j)++] = str[(*i)++];
	if (!str[*i])
	{
		fprintf(stderr, "minishell: syntax error: unclosed quotes\n");
		return (-1);
	}
	(*i)++;
	return (0);
}

int	sup_quotes(char **str, int i, int j)
{
	char quote_char;
	char *new_str;

	new_str = malloc(calc_len_new_str(*str) + 1);
	if (!neFunción principal que elimina las comillas y copia la cadena procesada
int	sup_quotes(char **str, int i, int j)
{w_str)
	{
		perror("minishell: memory allocation error");
		exit(EXIT_FAILURE);
	}
	while ((*str)[i])
	{
		if (is_quotes((*str)[i]))
		{
			quote_char = (*str)[i++];
			if (copy_within_quotes(*str, &i, quote_char, new_str, &j) == -1)
				return (handle_unclosed_quotes(str, new_str));
		}
		else
			new_str[j++] = (*str)[i++];
	}
	new_str[j] = '\0';
	free(*str);
	*str = new_str;
	return (0);
}

*/

int	sup_quotes(char **str, int i, int j);

char	**lexer(char *input)
{
	char	**tokens;
	int		i;

	i = 0;
	if (!input)
		return NULL;
	if (!are_quotes_closed(input))
	{
		perror("minishell: syntax error: unclosed quotes");
		g_exit_status = 1;
		return NULL;
	}
	tokens = parser_comand(input, &i);
	expand_all_vars(tokens);
	i = 0;
	while (tokens && tokens[i])
		sup_quotes(&(tokens[i++]), 0, 0);
	free(input);
	if (!tokens)
		return NULL;
	return tokens;
}
