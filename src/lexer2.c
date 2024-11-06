

#include "minishell.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

int	is_quotes(char c);
int	calc_len_new_str(char *str);
int	handle_unclosed_quotes(char **str, char *new_str);

typedef struct s_copy_data
{
	char *str;
	int *i;
	int *j;
	char quote_char;
	char *new_str;
}   t_copy_data;

void	init_data_structure(t_copy_data *data, char *str, int *i, int *j, char *new_str)
{
	data->str = str;
	data->i = i;
	data->j = j;
	data->new_str = new_str;
}

// Copia dentro de las comillas
int	copy_within_quotes(t_copy_data *data)
{
	while (data->str[*data->i] && data->str[*data->i] != data->quote_char)
		data->new_str[(*data->j)++] = data->str[(*data->i)++];
	if (!data->str[*data->i])
	{
		fprintf(stderr, "minishell: syntax error: unclosed quotes\n");
		return (-1);
	}
	(*data->i)++;
	return (0);
}

// Procesa el contenido entre comillas en la cadena original y lo copia
int	process_quotes(char **str, t_copy_data *data)
{
	while ((*str)[*data->i])
	{
		if (is_quotes((*str)[*data->i]))
		{
			data->quote_char = (*str)[(*data->i)++];
			if (copy_within_quotes(data) == -1)
				return (handle_unclosed_quotes(str, data->new_str));
		}
		else
			data->new_str[(*data->j)++] = (*str)[(*data->i)++];
	}
	return (0);
}

// Función principal que elimina las comillas y copia la cadena procesada
int	sup_quotes(char **str, int i, int j)
{
	t_copy_data data;
	char *new_str;

	new_str = malloc(calc_len_new_str(*str) + 1);
	if (!new_str)
	{
		perror("minishell: memory allocation error");
		exit(EXIT_FAILURE);
	}

	init_data_structure(&data, *str, &i, &j, new_str);

	if (process_quotes(str, &data) == -1)
		return (-1);

	data.new_str[*data.j] = '\0';
	free(*str);
	*str = data.new_str;
	return (0);
}
