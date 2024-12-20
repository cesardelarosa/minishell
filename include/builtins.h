/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <cde-la-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 17:50:20 by cde-la-r          #+#    #+#             */
/*   Updated: 2024/10/17 00:48:00 by cde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

typedef enum e_builtin
{
	BUILTIN_NONE,
	BUILTIN_CD,
	BUILTIN_PWD,
	BUILTIN_ECHO,
	BUILTIN_EXIT,
	BUILTIN_EXPORT,
	BUILTIN_UNSET,
	BUILTIN_ENV
}	t_builtin;

void	builtin_exit(char **args);
void	builtin_echo(char **args);
void	builtin_pwd(void);
void	builtin_cd(char **args);
void	builtin_export(char **args, char **envp);
void	builtin_unset(char **args);
void	builtin_env(char **envp);

#endif
