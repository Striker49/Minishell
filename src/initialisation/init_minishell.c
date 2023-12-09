/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seroy <seroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 21:22:33 by nomu              #+#    #+#             */
/*   Updated: 2023/12/08 19:33:36 by seroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_global		g_heredoc;

void	ft_boot_shell(t_minishell *shell, char **envp, int argc, char **argv)
{
	(void)argc;
	(void)argv;
	g_heredoc.child = 0;
	g_heredoc.stop = 0;
	tcgetattr(STDIN_FILENO, &shell->term);
	deactivate_ctrl(shell->term);
	shell->gcn = init_garbage_collector();
	signal(SIGINT, &interrupt);
	signal(SIGQUIT, SIG_IGN);
	init_environment(shell, envp);
	init_error_handling(shell);
	shell->state = 1;
}

void	ft_destroy_shell(t_minishell *shell)
{
	int	return_value;

	return_value = shell->error->exit_code;
	gc_collect(shell->gc);
	gc_collect(shell->gcn);
	exit(return_value);
}

int	ft_validate_quotes(t_minishell *shell, char *prompt)
{
	if (!ft_is_valid_quotes(prompt))
	{
		ft_handle_errno(shell, 1);
		gc_collect(shell->gc);
		return (0);
	}
	return (1);
}

void	ft_init_loop(t_minishell *shell, char **envp)
{
	(void)envp;
	shell->gc = init_garbage_collector();
	prompt_user(shell);
	if (shell->prompt[0] != '\0')
		add_history(shell->prompt);
	shell->envp = env_list_to_arr(shell, shell->gcn, shell->env_lst);
}
