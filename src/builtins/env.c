/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seroy <seroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 12:52:32 by jupallar          #+#    #+#             */
/*   Updated: 2023/12/01 14:38:57 by seroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/env.h"

t_env_list	*ft_create_env_node(t_garbage_collector *gc, char *env_elem)
{
	t_env_list	*new_node;

	new_node = (t_env_list *)gc_malloc(gc, sizeof(t_env_list));
	if (!new_node)
		return (NULL);
	new_node->elem = ft_gc_strdup(gc, env_elem);
	if (!new_node->elem)
	{
		gc_collect_address(gc, (void *)new_node);
		return (NULL);
	}
	new_node->env_var = gc_malloc(gc, sizeof(t_var));
	if (!new_node->env_var)
		return (NULL);
	new_node->env_var->key = ft_get_env_key(gc, env_elem);
	new_node->env_var->value = ft_get_env_value(gc, env_elem);
	new_node->env_var->v_len = count_value_len(env_elem);
	new_node->env_var->k_len = count_key_len(env_elem);
	new_node->next = NULL;
	new_node->prev = NULL;
	return (new_node);
}

void	ft_add_elem_to_end_of_list(t_garbage_collector *gc, t_env_list **head,
		char *env_str)
{
	t_env_list	*current;

	if (!*head)
		*head = ft_create_env_node(gc, env_str);
	else
	{
		current = *head;
		while (current->next != NULL)
			current = current->next;
		current->next = ft_create_env_node(gc, env_str);
		if (current->next)
			current->next->prev = current;
	}
}

void	ft_add_node_to_list(t_garbage_collector *gc, t_env_list **head,
		t_env_list **current, char *env_str)
{
	if (!*head)
	{
		*head = ft_create_env_node(gc, env_str);
		*current = *head;
	}
	else
	{
		(*current)->next = ft_create_env_node(gc, env_str);
		(*current)->next->prev = *current;
		*current = (*current)->next;
	}
}

t_env_list	*ft_build_env(t_garbage_collector *gc, char **envp)
{
	t_env_list	*head;
	t_env_list	*current;

	head = NULL;
	current = NULL;
	if (!envp || ft_count_table(envp) == 0)
		return (NULL);
	while (*envp)
	{
		ft_add_node_to_list(gc, &head, &current, *envp);
		if (!head || !current)
			return (NULL);
		envp++;
	}
	return (head);
}
