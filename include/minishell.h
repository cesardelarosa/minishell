/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <cde-la-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 22:18:26 by cde-la-r          #+#    #+#             */
/*   Updated: 2024/09/19 19:18:27 by cde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define WELCOME_MSG "\nWelcome to Minishell!\nType 'exit' to quit.\n\n"

char	**ft_free_split(char **result);
char	**parse_command(char *input);
void	setup_signal_handlers(void);
void	handle_command(char **args);
char	*read_input(void);

#endif
