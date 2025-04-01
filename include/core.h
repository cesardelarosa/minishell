/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <code@cesardelarosa.xyz>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 18:04:00 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/04/01 11:03:45 by cesi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CORE_H
# define CORE_H

# include "lexer.h"
# include "libft.h"
# include "structs.h"

void		init_signals(void);
char		*read_prompt(void);
t_pipeline	*parser(t_list *tokens, int status);
void		free_tokens(t_list *tokens);
int			exec(t_pipeline *p, char **envp);

#endif
