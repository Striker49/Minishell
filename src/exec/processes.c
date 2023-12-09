/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seroy <seroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 00:22:07 by nomu              #+#    #+#             */
/*   Updated: 2023/12/08 16:11:25 by seroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/exec.h"

void	set_pipes(t_command_list *cmd_node)
{
	if (cmd_node->pipe_fd[0] != STDIN_FILENO && cmd_node->pipe_fd[0] != -1)
	{
		if (dup2(cmd_node->pipe_fd[0], STDIN_FILENO) == -1)
		{
			perror("dup2");
			exit (1);
		}
	}
	if (cmd_node->pipe_fd[1] != STDOUT_FILENO)
	{
		if (dup2(cmd_node->pipe_fd[1], STDOUT_FILENO) == -1)
		{
			perror("dup2");
			exit(1);
		}
	}
}

void	execute_child_logic(t_minishell *shell, t_command_list *cmd_node,
		char **envp, int b_flag)
{
	const char	*path;
	char *const	*args;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	path = cmd_node->cmd[0];
	args = cmd_node->cmd;
	set_pipes(cmd_node);
	if (cmd_node->pipe_fd[0] != STDIN_FILENO && cmd_node->pipe_fd[0] != -1)
		ft_close(cmd_node->pipe_fd[0]);
	if (cmd_node->pipe_fd[1] != STDOUT_FILENO && cmd_node->pipe_fd[1] != -1)
		ft_close(cmd_node->pipe_fd[1]);
	if (!cmd_node->cmd[0])
		return ;
	b_flag = ft_is_builtin(cmd_node->cmd[0]);
	if (b_flag)
		ft_exec_builtin(shell, b_flag, cmd_node);
	else
	{
		execve(path, args, envp);
		perror("minishell");
		shell->error->exit_code = 126;
	}
}
