/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_creation.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <code@cesardelarosa.xyz>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 13:01:51 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/04/04 00:39:09 by cesi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_CREATION_H
# define STRUCT_CREATION_H

# include "structs.h"

char		**parse_args(const char *input);

t_redir		*redir_create(t_token_type type, char *file, t_command *parent_cmd);
void		redir_destroy(void *content);

t_command	*command_create(char *cmd_str);
void		command_destroy(void *cmd);
int			command_add_redir(t_command *cmd, t_token_type type, char *file);

t_pipeline	*pipeline_create(t_ctx *ctx);
void		pipeline_destroy(t_pipeline *pipeline);
int			pipeline_add_command(t_pipeline *p, t_command *cmd);

#endif
