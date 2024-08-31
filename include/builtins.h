/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <cde-la-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 17:50:20 by cde-la-r          #+#    #+#             */
/*   Updated: 2024/08/30 17:50:20 by cde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

void	builtin_exit(char **args);
void	builtin_echo(char **args);
void	builtin_pwd(void);
void	builtin_cd(char **args);

#endif