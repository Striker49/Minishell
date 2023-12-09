/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils5.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seroy <seroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 15:17:47 by jupallar          #+#    #+#             */
/*   Updated: 2023/12/08 19:29:35 by seroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/exec.h"
#include <signal.h>

t_global		g_heredoc;

int	ft_check_err_cases(t_minishell *shell, t_command_list *cmd_cursor)
{
	if (!*cmd_cursor->cmd)
	{
		shell->error->exit_code = 1;
		cmd_cursor = cmd_cursor->next;
		return (0);
	}
	else if (cmd_cursor->cmd[0][0] == '\0')
	{
		print_err_msg("minshell:", " :", "command not found\n");
		shell->error->exit_code = 127;
		return (1);
	}
	return (0);
}

void	handle_child_process_logic(t_minishell *shell,
		t_command_list *cmd_cursor, int b_flag, int pipetmp[2])
{
	if (pipetmp[0] != cmd_cursor->pipe_fd[0])
		ft_close(pipetmp[0]);
	if (pipetmp[1] != cmd_cursor->pipe_fd[1])
		ft_close(pipetmp[1]);
	execute_child_logic(shell, cmd_cursor, shell->envp, b_flag);
	ft_destroy_shell(shell);
}

void	handle_parent_process_logic(t_minishell *shell,
		t_command_list *cmd_cursor, int pipetmp[2])
{
	if (pipetmp[0] != -1)
		shell->exec->pipe_index = pipetmp[0];
	if (cmd_cursor->pipe_fd[0] != STDIN_FILENO)
		ft_close(cmd_cursor->pipe_fd[0]);
	if (pipetmp[1] != STDOUT_FILENO)
		ft_close(pipetmp[1]);
}

void	execute_child_process(t_minishell *shell, t_command_list *cmd_cursor,
		int b_flag, int pipetmp[2])
{
	static int	i;

	if (cmd_cursor->index == 0)
		i = 0;
	shell->exec->child_pid[i] = fork();
	g_heredoc.child = 1;
	shell->exec->child_nbr++;
	if (!cmd_cursor->next)
		shell->exec->last_pid = shell->exec->child_pid[i];
	if (shell->exec->child_pid[i] == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (shell->exec->child_pid[i] < 0)
		printf("error fork\n");
	if (shell->exec->child_pid[i] == 0)
		handle_child_process_logic(shell, cmd_cursor, b_flag, pipetmp);
	else
		handle_parent_process_logic(shell, cmd_cursor, pipetmp);
	i++;
}

void	setup_pipe_and_execute(t_minishell *shell, t_command_list *cmd_cursor,
		int b_flag)
{
	int	pipetmp[2];

	if (setup_pipe(pipetmp) == -1)
		perror("Pipe");
	if (cmd_cursor->index == 0 && cmd_cursor->pipe_fd[0] == -1)
		cmd_cursor->pipe_fd[0] = STDIN_FILENO;
	if (ft_count_commands(shell->exec->command_list) == cmd_cursor->index + 1
		&& cmd_cursor->pipe_fd[1] == -1)
	{
		cmd_cursor->pipe_fd[1] = STDOUT_FILENO;
		if (pipetmp[0] != 1)
			ft_close(pipetmp[0]);
		if (pipetmp[1] != 1)
			ft_close(pipetmp[1]);
	}
	if (cmd_cursor->pipe_fd[0] == -1)
		cmd_cursor->pipe_fd[0] = shell->exec->pipe_index;
	if (cmd_cursor->pipe_fd[1] == -1)
		cmd_cursor->pipe_fd[1] = pipetmp[1];
	signal(SIGINT, SIG_IGN);
	execute_child_process(shell, cmd_cursor, b_flag, pipetmp);
}
