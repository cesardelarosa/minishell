/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <code@cesardelarosa.xyz>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 18:04:00 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/06/18 15:51:12 by cesi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CORE_H
# define CORE_H

# include "lexer.h"
# include "libft.h"
# include "structs.h"

char		*read_prompt(int status);
t_pipeline	*parser(t_list *tokens, t_ctx *ctx);
void		free_tokens(t_list *tokens);
int			exec(t_pipeline *p);
t_ctx		init_ctx(char **envp);
void		destroy_ctx(t_ctx *ctx);

#endif
