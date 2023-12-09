/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seroy <seroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 17:50:54 by jupallar          #+#    #+#             */
/*   Updated: 2023/12/09 16:40:17 by seroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	create_and_add_env_elem(t_minishell *shell, char *key, char *value)
{
	ft_create_env_node(shell->gcn, key);
	ft_add_elem_to_end_of_list(shell->gcn, &shell->env_lst, value);
}

void	update_env_elem(t_minishell *shell, t_env_list *elem, char *value, 
	char **var_table)
{
	if (var_table[1])
	{
		elem->elem = ft_gc_strdup(shell->gcn, value);
		elem->env_var->key = ft_gc_strdup(shell->gcn, var_table[0]);
		elem->env_var->value = ft_gc_strdup(shell->gcn, var_table[1]);
	}
	else
	{
		elem->elem = ft_gc_strdup(shell->gcn, value);
		elem->env_var->key = ft_gc_strdup(shell->gcn, var_table[0]);
		elem->env_var->value = ft_gc_strdup(shell->gcn, "");
	}
	elem->env_var->k_len = ft_strlen(elem->env_var->key);
	elem->env_var->v_len = ft_strlen(elem->env_var->value);
}

void	handle_valid_export_var(t_minishell *shell, char *value)
{
	char		**key_value;
	t_env_list	*elem;

	key_value = ft_gc_split(shell->gcn, value, '=');
	if (key_value && key_value[0])
	{
		elem = find_env_elem(shell, key_value[0]);
		if (elem)
			update_env_elem(shell, elem, value, key_value);
		else
			create_and_add_env_elem(shell, key_value[0], value);
	}
	shell->error->exit_code = 0;
}

void	handle_export_iteration(t_minishell *shell, t_token_list **current)
{
	*current = (*current)->next;
	while (*current && (*current)->token.type != PIPE)
	{
		if (ft_is_valid_export_var(shell, (*current)->token.value))
			handle_valid_export_var(shell, (*current)->token.value);
		else
			shell->error->exit_code = 1;
		*current = (*current)->next;
	}
}

int	ft_export(t_minishell *shell, char **envp)
{
	t_token_list	*current;

	if (!envp)
		return (0);
	current = shell->tokens;
	if (print_all_vars(shell, envp, current))
		return (0);
	while (current)
	{
		handle_export_iteration(shell, &current);
	}
	return (0);
}
