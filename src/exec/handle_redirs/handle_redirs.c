/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <code@cesardelarosa.xyz>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 12:27:28 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/06/21 12:14:00 by cde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "handle_redir.h"
#include "structs.h"

static void	close_and_free_fd(void *content)
{
	int	fd;

	fd = *(int *)content;
	if (fd >= 0)
		close(fd);
	free(content);
}

static int	prepare_heredocs(t_list *redirs, t_list **heredoc_fds)
{
	t_redir	*r;
	int		*p_fd;

	while (redirs)
	{
		r = (t_redir *)redirs->content;
		if (r->type == REDIR_HEREDOC)
		{
			p_fd = malloc(sizeof(int));
			if (!p_fd)
			{
				ft_lstclear(heredoc_fds, &close_and_free_fd);
				return (-1);
			}
			*p_fd = handle_heredoc(r);
			ft_lstadd_back(heredoc_fds, ft_lstnew(p_fd));
			if (*p_fd < 0)
				return (*p_fd);
		}
		redirs = redirs->next;
	}
	return (0);
}

static int	apply_redirections(t_list *redirs, t_list *heredoc_fds)
{
	t_redir	*r;
	t_list	*current_heredoc_node;
	int		status;

	status = 0;
	current_heredoc_node = heredoc_fds;
	while (redirs && status == 0)
	{
		r = (t_redir *)redirs->content;
		if (r->type == REDIR_INPUT)
			status = handle_redir_in(r);
		else if (r->type == REDIR_OUTPUT)
			status = handle_redir_out(r);
		else if (r->type == REDIR_APPEND)
			status = handle_redir_append(r);
		else if (r->type == REDIR_HEREDOC)
		{
			if (dup2(*(int *)current_heredoc_node->content, STDIN_FILENO) < 0)
				status = -1;
			current_heredoc_node = current_heredoc_node->next;
		}
		redirs = redirs->next;
	}
	return (status);
}

int	handle_redirs(t_list *redirs)
{
	t_list	*heredoc_fds;
	int		status;
	int		prep_status;

	heredoc_fds = NULL;
	prep_status = prepare_heredocs(redirs, &heredoc_fds);
	if (prep_status != 0)
	{
		ft_lstclear(&heredoc_fds, &close_and_free_fd);
		if (prep_status == -2)
			return (130);
		return (-1);
	}
	status = apply_redirections(redirs, heredoc_fds);
	ft_lstclear(&heredoc_fds, &close_and_free_fd);
	return (status);
}
