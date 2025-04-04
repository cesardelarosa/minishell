/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <code@cesardelarosa.xyz>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 10:21:49 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/04/04 10:56:36 by cde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_BUILTINS_H
# define FT_BUILTINS_H

# include "env.h"

int	ft_echo(char **argv, t_env *env);
int	ft_cd(char **argv, t_env *env);
int	ft_pwd(char **argv, t_env *env);
int	ft_export(char **argv, t_env *env);
int	ft_unset(char **argv, t_env *env);
int	ft_env(char **argv, t_env *env);
int	ft_exit(char **argv, t_env *env);

#endif
