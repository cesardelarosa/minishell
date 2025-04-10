/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <code@cesardelarosa.xyz>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 18:08:20 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/04/07 17:35:11 by cesi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"
#include "struct_creation.h"
#include <stdio.h>
#include <stdlib.h>

void	update_last_arg(t_list *arg_lst, char *new_content)
{
	t_list	*current;

	if (!arg_lst || !new_content)
		return ;
	current = arg_lst;
	while (current->next)
		current = current->next;
	free(current->content);
	current->content = new_content;
}
