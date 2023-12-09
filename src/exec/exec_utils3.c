/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seroy <seroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 15:15:29 by jupallar          #+#    #+#             */
/*   Updated: 2023/12/09 16:39:15 by seroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/exec.h"
#include <signal.h>

t_global	g_heredoc;

void	handle_child_process_completion(t_minishell *shell, int status)
{
	int	i;

	i = 0;
	while (i < shell->exec->child_nbr)
	{
		waitpid(shell->exec->child_pid[i], &status, 0);
		if (WIFEXITED(status) == 1
			&& shell->exec->child_pid[i] == shell->exec->last_pid
			&& shell->keep_ex == 0)
			shell->error->exit_code = (WEXITSTATUS(status));
		else if (WIFSIGNALED(status) == 1
			&& shell->exec->child_pid[i] == shell->exec->last_pid)
			shell->error->exit_code = (128 + WTERMSIG(status));
		else if (WIFSTOPPED(status) == 1
			&& shell->exec->child_pid[i] == shell->exec->last_pid)
			shell->error->exit_code = (128 + WSTOPSIG(status));
		g_heredoc.child = 0;
		i++;
	}
	tcgetattr(STDIN_FILENO, &shell->term);
	deactivate_ctrl(shell->term);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, &interrupt);
}

void	ft_exec_loop(t_minishell *shell)
{
	int				b_flag;
	int				r_flag;
	int				status;
	t_command_list	*cmd_cursor;

	b_flag = 0;
	r_flag = 0;
	status = 0;
	cmd_cursor = shell->exec->command_list;
	handle_child_absence_and_redirections(shell, &r_flag, cmd_cursor);
	cmd_cursor = shell->exec->command_list;
	while (cmd_cursor != NULL && g_heredoc.stop == 0)
	{
		ft_execute(shell, cmd_cursor, b_flag);
		if (g_heredoc.stop == 1)
			break ;
		cmd_cursor = cmd_cursor->next;
	}
	if (shell->exec->child_pid)
		handle_child_process_completion(shell, status);
	gc_collect(shell->gc);
}

void	ft_init_exec_process(t_minishell *shell)
{
	init_executor(shell);
	shell->exec->command_list = ft_build_commands(shell, shell->tokens);
	if (!shell->exec->command_list)
		return ;
}

void	ft_process_commands(t_minishell *shell)
{
	if (shell->tokens->len > 0)
	{
		ft_find_dollar_sign(shell->gc, &shell->tokens, shell->env_lst, shell);
		ft_init_exec_process(shell);
		ft_exec_loop(shell);
	}
	else
		return ;
}

int	ft_process_loop(t_minishell *shell)
{
	init_tokenizer(shell);
	shell->tokens = tokenizer(shell, shell->prompt);
	if (shell->tokens)
		shell->tokens->len = ft_count_tokens(shell->tokens);
	if (!ft_validate_syntax(shell))
		return (0);
	else
		ft_process_commands(shell);
	g_heredoc.stop = 0;
	return (1);
}
