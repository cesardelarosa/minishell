/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <code@cesardelarosa.xyz>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 10:13:50 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/04/10 11:35:25 by cesi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "structs.h"

typedef int			(*t_builtin_ft)(char **argv, t_env *env);

typedef struct s_builtin
{
	char			*name;
	t_builtin_ft	func;
}					t_builtin;

t_builtin_ft		get_builtin_ft(char *cmd);

#endif
