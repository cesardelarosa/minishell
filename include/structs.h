/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <code@cesardelarosa.xyz>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 13:01:51 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/06/24 12:20:13 by cde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "env.h"
# include "libft.h"

typedef enum e_redir_type
{
	REDIR_INPUT,
	REDIR_OUTPUT,
	REDIR_APPEND,
	REDIR_HEREDOC
}							t_redir_type;

typedef struct s_ctx
{
	char					*prog_name;
	char					**envp;
	t_env					*env;
	int						status;
}							t_ctx;

typedef struct s_command	t_command;

typedef struct s_redir
{
	t_redir_type			type;
	char					*file;
	t_command				*cmd;
	char					*heredoc_buf;
}							t_redir;

typedef struct s_pipeline
{
	t_list					*commands;
	unsigned int			cmd_count;
	int						**pipes;
	pid_t					*pids;
	t_ctx					*ctx;
}							t_pipeline;

typedef struct s_command
{
	char					**argv;
	t_list					*redirs;
	t_pipeline				*p;
}							t_command;

typedef int					(*t_token_parser_ft)(t_command *, t_list **,
						t_list **, t_ctx *);

#endif
