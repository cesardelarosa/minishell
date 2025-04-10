/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error_token.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <code@cesardelarosa.xyz>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 21:25:35 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/04/05 21:25:36 by cde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	parse_error(t_token *token)
{
	ft_putstr_fd("Error: ", 2);
	ft_putstr_fd(token->value, 2);
	ft_putstr_fd("\n", 2);
	return (0);
}
