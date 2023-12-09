/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seroy <seroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 22:46:42 by nomu              #+#    #+#             */
/*   Updated: 2023/11/23 18:33:13 by seroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/exec.h"

t_command_list	*ft_new_cmd_node(t_garbage_collector *gc,
								char **cmd_table,
								int index,
								t_redir_list *redir_head)
{
	t_command_list	*new_node;

	new_node = gc_malloc(gc, sizeof(t_command_list));
	if (!new_node)
		return (NULL);
	new_node->cmd = cmd_table;
	new_node->index = index;
	new_node->pipe_fd[0] = -1;
	new_node->pipe_fd[1] = -1;
	new_node->redir_head = redir_head;
	new_node->next = NULL;
	return (new_node);
}

void	ft_add_cmd_to_list(t_garbage_collector *gc, char **cmd_table,
		t_cmd_vars *cmd_vars)
{
	if (!cmd_vars->head_cmd)
	{
		cmd_vars->head_cmd = ft_new_cmd_node(gc, cmd_table, cmd_vars->index++,
				cmd_vars->redir_list);
		cmd_vars->current_cmd = cmd_vars->head_cmd;
	}
	else
	{
		cmd_vars->current_cmd->next = ft_new_cmd_node(gc, cmd_table,
				cmd_vars->index++, cmd_vars->redir_list);
		cmd_vars->current_cmd = cmd_vars->current_cmd->next;
	}
}

void	init_cmd_vars(t_cmd_vars *cmd_vars, t_token_list *tokens)
{
	cmd_vars->current_cmd = NULL;
	cmd_vars->head_cmd = NULL;
	cmd_vars->token_cursor = tokens;
	cmd_vars->index = 0;
	cmd_vars->redir_list = NULL;
	cmd_vars->cmd = NULL;
}

t_command_list	*ft_build_commands(t_minishell *shell, t_token_list *tokens)
{
	t_cmd_vars	cmd_vars;

	init_cmd_vars(&cmd_vars, tokens);
	while (cmd_vars.token_cursor)
	{
		cmd_vars.redir_list = ft_build_redir_lst(shell, &cmd_vars.token_cursor);
		cmd_vars.cmd = ft_split_command(shell, &cmd_vars.token_cursor);
		ft_add_cmd_to_list(shell->gc, cmd_vars.cmd, &cmd_vars);
		if (cmd_vars.token_cursor && cmd_vars.token_cursor->token.type == PIPE)
			cmd_vars.token_cursor = cmd_vars.token_cursor->next;
	}
	shell->exec->command_list = cmd_vars.head_cmd;
	return (cmd_vars.head_cmd);
}
