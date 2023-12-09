/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   init_data.c                                        ██╗  ██╗██████╗       */
/*                                                      ██║  ██║╚════██╗      */
/*   By: jupallar <jupallar@student.42.qc>              ███████║ █████╔╝      */
/*                                                      ╚════██║██╔═══╝       */
/*   Created: 2023/12/01 14:56:42 by jupallar                ██║███████╗      */
/*   Updated: 2023/12/06 16:59:43 by jupallar                ╚═╝╚══════╝.qc   */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	init_tokenizer(t_minishell *shell)
{
	shell->tokenizer = gc_malloc(shell->gc, sizeof(t_tokenizer));
	if (!shell->tokenizer)
		exit(1);
	shell->tokenizer->len = ft_strlen(shell->prompt);
	shell->tokenizer->head = NULL;
}

void	init_executor(t_minishell *shell)
{
	shell->exec = gc_malloc(shell->gc, sizeof(t_executor));
	if (!shell->exec)
		exit(1);
	shell->exec->bin_path = NULL;
	shell->exec->table = NULL;
	shell->exec->command_list = NULL;
	shell->exec->redir_list = NULL;
	shell->exec->pipe_index = -1;
	shell->exec->table = NULL;
	shell->exec->child_pid = gc_malloc(shell->gc, sizeof(pid_t)
			* (ft_count_token_type(shell->tokens, PIPE) + 2));
	shell->exec->last_pid = 0;
	shell->exec->child_nbr = 0;
}

void	init_environment(t_minishell *shell, char **envp)
{
	shell->env_lst = gc_malloc(shell->gcn, sizeof(t_env_list));
	if (!shell->env_lst)
		exit(1);
	shell->env_lst->elem = NULL;
	shell->env_lst->env_var = NULL;
	duplicate_env(shell->gcn, shell, envp);
	shell->state = 1;
}

void	prompt_user(t_minishell *shell)
{
	shell->prompt = readline(MIKBLUE "minishell-1.0$ " WHITE);
	if (!shell->prompt)
	{
		shell->state = 0;
		shell->error->exit_code = 0;
		ft_destroy_shell(shell);
	}
	shell->keep_ex = 0;
}

void	init_error_handling(t_minishell *shell)
{
	shell->error = gc_malloc(shell->gcn, sizeof(t_errno));
	if (!shell->error)
		exit(1);
	shell->error->fd = 0;
	shell->error->exit_code = 0;
}
