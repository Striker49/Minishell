/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seroy <seroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 19:25:03 by seroy             #+#    #+#             */
/*   Updated: 2023/12/01 13:33:28 by seroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_is_valid_unset_var(t_minishell *shell, char *string)
{
	int	i;

	i = 0;
	if (ft_isalpha(string[0]) || string[0] == '_')
		i++;
	else
	{
		shell->error->exit_code = 1;
		printf("not valid id\n");
		return (0);
	}
	while (ft_isalnum(string[i]) || string[i] == '_')
	{
		i++;
	}
	if (string[i] == '\0')
	{
		return (1);
	}
	shell->error->exit_code = 1;
	printf("not valid id\n");
	return (0);
}

t_env_list	*rm_env_node(t_minishell *shell, t_env_list *current)
{
	if (current == shell->env_lst)
	{
		shell->env_lst = current->next;
		if (current->next != NULL)
			current->next->prev = NULL;
	}
	else
	{
		current->prev->next = current->next;
		if (current->next != NULL)
			current->next->prev = current->prev;
	}
	gc_collect_address(shell->gcn, current);
	return (current);
}

void	ft_unset(t_minishell *shell, t_command_list *command_list)
{
	t_env_list		*current;
	t_token_list	*token_cursor;
	char			*var;

	(void)command_list;
	if (shell->tokens->len < 2)
		return ;
	token_cursor = shell->tokens;
	while (token_cursor)
	{
		if (ft_is_valid_export_var(shell, token_cursor->token.value))
		{
			var = token_cursor->token.value;
			current = find_env_elem(shell, var);
			if (current != NULL)
				current = rm_env_node(shell, current);
		}
		token_cursor = token_cursor->next;
		shell->error->exit_code = 0;
	}
}
