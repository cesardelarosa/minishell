/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <cde-la-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 20:45:46 by cde-la-r          #+#    #+#             */
/*   Updated: 2024/09/19 13:59:32 by cde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROMPT_H
# define PROMPT_H

# define RESET			"\033[0m"
# define BOLD_RESET		"\033[1;0m"
# define BOLD_BLACK		"\033[1;90m"
# define BOLD_RED		"\033[1;91m"
# define BOLD_GREEN		"\033[1;92m"
# define BOLD_YELLOW		"\033[1;93m"
# define BOLD_BLUE		"\033[1;94m"
# define BOLD_MAGENTA		"\033[1;95m"
# define BOLD_CYAN		"\033[1;96m"
# define BOLD_WHITE		"\033[1;97m"

char	*ft_strjoin_free(char *s1, const char *s2);
char	*get_user(void);
char	*get_host(void);
char	*get_path(void);
char	*get_git_branch(void);

#endif
