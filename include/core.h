/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <code@cesardelarosa.xyz>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 18:04:00 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/03/31 19:07:44 by cesi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CORE_H
# define CORE_H

# include "lexer.h"
# include "libft.h"
# include "structs.h"

void		init_signals(void);
char		*read_line(char **envp);
t_pipeline	*parse_tokens(t_list *tokens);
void		free_tokens(t_list *tokens);

#endif
