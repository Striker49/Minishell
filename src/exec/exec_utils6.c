/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   exec_utils6.c                                      ██╗  ██╗██████╗       */
/*                                                      ██║  ██║╚════██╗      */
/*   By: jupallar <jupallar@student.42.qc>              ███████║ █████╔╝      */
/*                                                      ╚════██║██╔═══╝       */
/*   Created: 2023/12/05 15:18:55 by jupallar                ██║███████╗      */
/*   Updated: 2023/12/06 15:06:42 by jupallar                ╚═╝╚══════╝.qc   */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/exec.h"
#include <signal.h>

t_global		g_heredoc;

t_redir_list	*setup_outfile_redirection(t_minishell *shell,
										t_redir_list *redir_list,
										int pipe_fd[2])
{
	redir_list->fd = open(redir_list->file_name, O_WRONLY | O_CREAT | O_TRUNC,
			0644);
	if (redir_list->fd == -1)
	{
		print_err_msg("minishell: ", redir_list->file_name,
			": Permission denied\n");
		shell->error->exit_code = 1;
		return (NULL);
	}
	pipe_fd[1] = redir_list->fd;
	return (redir_list);
}

t_redir_list	*setup_redirections(t_minishell *shell,
									t_redir_list *redir_list,
									int pipe_fd[2])
{
	if (redir_list->type == HEREDOC)
		return (setup_heredoc_redirection(shell, redir_list, pipe_fd));
	else if (redir_list->type == APPEND)
		return (setup_append_redirection(shell, redir_list, pipe_fd));
	else if (redir_list->type == INFILE)
		return (setup_infile_redirection(shell, redir_list, pipe_fd));
	else if (redir_list->type == OUTFILE)
		return (setup_outfile_redirection(shell, redir_list, pipe_fd));
	return (redir_list);
}

int	ft_validate_syntax(t_minishell *shell)
{
	if (!shell->tokens)
		return (0);
	if (!ft_is_valid_syntax(shell->tokens))
	{
		ft_handle_errno(shell, 2);
		shell->error->exit_code = 2;
		return (0);
	}
	return (1);
}

void	ft_cmd_redir(t_minishell *shell, t_redir_list *head, int r_flag)
{
	while (head && g_heredoc.stop == 0)
	{
		r_flag = ft_redir_switch(head);
		if (r_flag)
			ft_exec_redir(shell, head);
		head = head->next;
	}
}

int	ft_init_redirs(t_minishell *shell, t_command_list *cmd_cursor)
{
	t_redir_list	*temp;

	if (cmd_cursor->redir_head)
	{
		temp = cmd_cursor->redir_head;
		while (temp)
		{
			temp = setup_redirections(shell, temp, cmd_cursor->pipe_fd);
			if (!temp)
				return (1);
			temp = temp->next;
		}
	}
	return (0);
}
