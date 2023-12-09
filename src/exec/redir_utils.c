/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seroy <seroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 16:40:16 by jupallar          #+#    #+#             */
/*   Updated: 2023/12/08 14:34:56 by seroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/exec.h"
#include "../../inc/minishell.h"
#include <signal.h>

int	handle_append(t_redir_list *redir)
{
	redir->fd = open(redir->file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (redir->fd == -1)
		return (0);
	ft_close(redir->fd);
	return (1);
}

int	handle_outfile(t_redir_list *redir)
{
	redir->fd = open(redir->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (redir->fd == -1)
		return (0);
	ft_close(redir->fd);
	return (1);
}

int	handle_infile(t_redir_list *redir)
{
	redir->fd = open(redir->file_name, O_RDONLY);
	if (redir->fd == -1)
		return (0);
	ft_close(redir->fd);
	return (1);
}

int	ft_exec_redir(t_minishell *shell, t_redir_list *redir_list)
{
	int	error;

	error = 0;
	if (redir_list->type == HEREDOC)
		error = handle_heredoc(shell, redir_list);
	else if (redir_list->type == APPEND)
		error = handle_append(redir_list);
	else if (redir_list->type == OUTFILE)
		error = handle_outfile(redir_list);
	else if (redir_list->type == INFILE)
		error = handle_infile(redir_list);
	return (error);
}

int	ft_redir_switch(t_redir_list *redir_list)
{
	if (redir_list->type == HEREDOC)
		return (6);
	else if (redir_list->type == APPEND)
		return (5);
	else if (redir_list->type == INFILE)
		return (4);
	else if (redir_list->type == OUTFILE)
		return (3);
	return (0);
}
