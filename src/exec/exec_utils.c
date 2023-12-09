/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seroy <seroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 00:18:22 by nomu              #+#    #+#             */
/*   Updated: 2023/12/01 16:44:58 by seroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/exec.h"

int	ft_count_commands(t_command_list *cmds)
{
	int				i;
	t_command_list	*temp;

	i = 0;
	temp = cmds;
	while (temp != NULL)
	{
		temp = temp->next;
		i++;
	}
	return (i);
}

int	ft_count_tokens(t_token_list *tokens)
{
	int				i;
	t_token_list	*temp;

	i = 0;
	temp = tokens;
	while (temp != NULL && temp->token.type != PIPE)
	{
		temp = temp->next;
		i++;
	}
	return (i);
}

int	ft_count_next_pipe(t_token_list *current)
{
	int	count;

	count = 0;
	while (current && current->token.type != PIPE)
	{
		count++;
		current = current->next;
	}
	return (count);
}

char	**cmd_split(t_minishell *shell, t_token_list **current, 
	t_token_list ***token_ptr, int *i)
{
	int		cmd_len;
	char	**cmd_table;

	cmd_table = shell->exec->table;
	cmd_len = ft_count_next_pipe((*current));
	while ((*current) && (*i) < cmd_len)
	{
		if ((*current)->token.value == 0)
			(*current) = (*current)->next->next;
		if (ft_is_redir((*current)->token.type))
			(*current) = (*current)->next->next;
		else if ((*current)->token.type == PIPE)
		{
			cmd_table[(*i)] = NULL;
			(**token_ptr) = (*current);
			return (cmd_table);
		}
		else
		{
			cmd_table[(*i)] = ft_gc_strdup(shell->gc, (*current)->token.value);
			(*current) = (*current)->next;
			(*i)++;
		}
	}
	return (cmd_table);
}

char	**ft_split_command(t_minishell *shell, t_token_list **token_ptr)
{
	int				i;
	int				cmd_len;
	t_token_list	*current;

	i = 0;
	current = *token_ptr;
	cmd_len = ft_count_next_pipe(current);
	if (!current)
		return (NULL);
	shell->exec->table = gc_malloc(shell->gc, sizeof(char *) * (cmd_len + 1));
	shell->exec->table = cmd_split(shell, &current, &token_ptr, &i);
	shell->exec->table[i] = NULL;
	*token_ptr = current;
	return (shell->exec->table);
}
