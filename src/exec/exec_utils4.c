/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seroy <seroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 15:16:57 by jupallar          #+#    #+#             */
/*   Updated: 2023/12/08 19:28:12 by seroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/exec.h"
#include <signal.h>

t_global	g_heredoc;

int	is_builtin_command(t_command_list *cmd_cursor)
{
	if (!cmd_cursor->cmd[0])
		return (0);
	if (!ft_strncmp("cd",
			cmd_cursor->cmd[0], 2) || !ft_strncmp("export",
			cmd_cursor->cmd[0], 6) || !ft_strncmp("unset",
			cmd_cursor->cmd[0], 6) || !ft_strncmp("exit",
			cmd_cursor->cmd[0], 5))
		return (1);
	return (0);
}

void	execute_builtin_command(t_minishell *shell, t_command_list *cmd_cursor)
{
	int	b_flag;

	b_flag = ft_is_builtin(cmd_cursor->cmd[0]);
	if (b_flag)
		ft_exec_builtin(shell, b_flag, cmd_cursor);
}

void	ft_attribute_pipes_fd(t_minishell *shell, t_command_list *cmd_cursor,
		int b_flag)
{
	if (is_builtin_command(cmd_cursor)
		&& ft_count_commands(shell->exec->command_list) == 1)
		execute_builtin_command(shell, cmd_cursor);
	else
		setup_pipe_and_execute(shell, cmd_cursor, b_flag);
}

void	ft_execute(t_minishell *shell, t_command_list *cmd_cursor, int b_flag)
{
	if (ft_check_err_cases(shell, cmd_cursor))
		return ;
	if (validate_path(shell, cmd_cursor->cmd))
	{
		shell->keep_ex = 0;
		if (ft_init_redirs(shell, cmd_cursor))
			return ;
		ft_attribute_pipes_fd(shell, cmd_cursor, b_flag);
	}
}

void	handle_child_absence_and_redirections(t_minishell *shell, int *r_flag,
		t_command_list *cmd_cursor)
{
	if (!shell->exec->child_pid)
	{
		gc_collect(shell->gc);
		return ;
	}
	while (cmd_cursor != NULL)
	{
		ft_cmd_redir(shell, cmd_cursor->redir_head, *r_flag);
		cmd_cursor = cmd_cursor->next;
	}
}
