/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <code@cesardelarosa.xyz>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 10:21:49 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/04/01 10:47:52 by cesi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_BUILTINS_H
# define FT_BUILTINS_H

int	ft_cd(char **argv, char **envp);
int	ft_echo(char **argv, char **envp);
int	ft_pwd(char **argv, char **envp);
int	ft_exit(char **argv, char **envp);
int	ft_env(char **argv, char **envp);
int	ft_export(char **argv, char **envp);
int	ft_unset(char **argv, char **envp);

#endif
