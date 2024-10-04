/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrian <adrian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 13:39:56 by cde-la-r          #+#    #+#             */
/*   Updated: 2024/10/04 09:26:14 by adrian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

/*
** Checks if all quotes in the input string are properly closed.
** Counts the number of single and double quotes and returns true
** if both are even, indicating that they are closed.
**
** @param input: The string to check for closed quotes.
** @return: 1 if quotes are closed, 0 otherwise.
*/
int g_exit_err_val = 0;

/*
** The lexer function splits the input string into an array of tokens.
** It uses whitespace (' ') as the delimiter. After tokenization, the
** input string is freed since it's no longer needed.
**
** @param input: The input string to be tokenized.
** @return: A NULL-terminated array of strings (tokens).
*/

int get_exit_status(char **tokens)
{
    pid_t pid;
    int status;

    pid = fork();
    if (pid == -1)
    {
        perror("minishell: fork error");
        return -1; // Error en fork
    }
    else if (pid == 0)
    {
        // Ejecutar el comando
        if (execvp(tokens[0], tokens) == -1)
        {
            perror("minishell: exec error");
            exit(1); // Salir con error si exec falla
        }
    }
    else
    {
        // Esperar a que el proceso hijo termine
        if (waitpid(pid, &status, 0) == -1)
        {
            perror("minishell: waitpid error");
            return -1; // Error en waitpid
        }

        // Verificar si el proceso terminó correctamente
        if (WIFEXITED(status))
        {
            return WEXITSTATUS(status); // Retornar el código de salida
        }
    }
    return -1; // El comando no terminó correctamente
}

int is_quotes(char c)
{
    return (c == '\'' || c == '\"');
}

int are_quotes_closed(const char *str)
{
    int i = 0;
    char quote_char;

    // Verificar si la cadena es nula
    if (str == NULL)
    {
        fprintf(stderr, "Error: Cadena nula\n");
        return (0);
    }

    while (str[i])
    {
        printf("i = %d, str[i] = %c\n", i, str[i]); // Depuración

        // Verificar si el carácter actual es una comilla
        if (is_quotes(str[i]))
        {
            // Guardar el tipo de comilla encontrada (simple o doble)
            quote_char = str[i];
            i++;

            // Recorrer hasta encontrar la comilla de cierre o el final de la cadena
            while (str[i] && str[i] != quote_char)
            {
                printf("Dentro del bucle interno: i = %d, str[i] = %c\n", i, str[i]); // Depuración
                i++;
            }

            // Si no se encontró la comilla de cierre
            if (str[i] == '\0')
            {
                // Imprimir mensaje de error con el tipo de comilla no cerrada
                fprintf(stderr, "Error: Comillas '%c' no cerradas\n", quote_char);
                return (0); // Retornar 0 si las comillas no están cerradas
            }
        }
        i++;
    }
    return (1); // Retornar 1 si todas las comillas están cerradas
}

char **lexer(char *input)
{
    char **tokens;

    if (!input)
        return (NULL);

    /* Verificar si las comillas están cerradas
    if (!are_quotes_closed(input))
    {
        fprintf(stderr, "minishell: unclosed quotes\n");
        free(input); // Liberar la memoria de input
        g_exit_err_val = 1; // Guardar un código de error en caso de comillas no cerradas
        return (NULL); // Retornar NULL si hay error
    }*/

    tokens = ft_split(input, ' ');
    if (!tokens)
    {
        return (NULL); // Retornar NULL si hay error en ft_split
    }

    expand_all_vars(tokens); // Expandir variables de entorno en tokens

    // Ejecutar el comando y capturar el estado de salida
    g_exit_err_val = get_exit_status(tokens); // Guardar el código de salida del último comando

    return (tokens);
}