/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils7.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seroy <seroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 15:20:38 by jupallar          #+#    #+#             */
/*   Updated: 2023/12/09 12:19:31 by seroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/exec.h"
#include <signal.h>

t_global		g_heredoc;

t_redir_list	*setup_heredoc_redirection(t_minishell *shell,
										t_redir_list *redir_list,
										int pipe_fd[2])
{
	redir_list->fd = open(redir_list->file_name, O_RDONLY);
	if (redir_list->fd == -1)
	{
		if (errno == EACCES)
			print_err_msg("minishell: ", redir_list->file_name,
				": Permission denied\n");
		else
		{
			print_err_msg("minishell: ", redir_list->file_name,
				": No such file or directory\n");
		}
		shell->error->exit_code = 1;
		return (NULL);
	}
	pipe_fd[0] = redir_list->fd;
	return (redir_list);
}

t_redir_list	*setup_append_redirection(t_minishell *shell,
										t_redir_list *redir_list,
										int pipe_fd[2])
{
	redir_list->fd = open(redir_list->file_name, O_WRONLY | O_CREAT | O_APPEND,
			0644);
	if (redir_list->fd == -1)
	{
		if (errno == EACCES)
			print_err_msg("minishell: ", redir_list->file_name,
				": Permission denied\n");
		else
		{
			print_err_msg("minishell: ", redir_list->file_name,
				": No such file or directory\n");
		}
		shell->error->exit_code = 1;
		return (NULL);
	}
	pipe_fd[1] = redir_list->fd;
	return (redir_list);
}

t_redir_list	*setup_infile_redirection(t_minishell *shell,
										t_redir_list *redir_list,
										int pipe_fd[2])
{
	redir_list->fd = open(redir_list->file_name, O_RDONLY);
	if (access(redir_list->file_name, R_OK) == -1)
	{
		redir_list->fd = open("/dev/null", O_RDONLY);
		print_err_msg("minishell: ", redir_list->file_name,
			": No such file or directory\n");
		shell->error->exit_code = 1;
		shell->keep_ex = 1;
	}
	if (redir_list->fd == -1)
	{
		print_err_msg("minishell: ", redir_list->file_name,
			": No such file or directory\n");
		shell->error->exit_code = 1;
		pipe_fd[1] = STDOUT_FILENO;
		return (NULL);
	}
	pipe_fd[0] = redir_list->fd;
	return (redir_list);
}

void	exit_hd(t_minishell *shell)
{
	ft_close(g_heredoc.fd);
	free(g_heredoc.delimiter);
	shell->error->exit_code = 1;
	g_heredoc.stop = 1;
}
