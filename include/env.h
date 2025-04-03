/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <code@cesardelarosa.xyz>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 00:18:27 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/04/04 00:43:55 by cesi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

typedef struct s_envvar
{
	char			*key;
	char			*value;
	struct s_envvar	*next;
}					t_envvar;

typedef struct s_env
{
	t_envvar		*head;
}					t_env;

t_env				*env_init(char **envp);
char				*env_get(t_env *env, const char *key);
int					env_set(t_env *env, const char *key, const char *value,
						int overwrite);
int					env_unset(t_env *env, const char *key);
char				**env_to_array(t_env *env);
void				env_destroy(t_env *env);

#endif
