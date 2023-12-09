/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seroy <seroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 13:34:43 by jupallar          #+#    #+#             */
/*   Updated: 2023/12/06 12:09:34 by seroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/env.h"

void	duplicate_env(t_garbage_collector *gc, t_minishell *shell, char **envp)
{
	size_t		env_len;
	t_env_list	*env;

	if (!envp)
		return ;
	env_len = ft_count_table(envp);
	if (env_len == 0)
	{
		shell->envp = NULL;
		return ;
	}
	shell->envp = ft_gc_table_dup(gc, envp);
	env = ft_build_env(gc, envp);
	shell->env_lst = env;
}

void	print_env(t_minishell *shell, char **new_table, int len)
{
	int			i;
	t_env_list	*current;

	i = 0;
	current = shell->env_lst;
	while (new_table && i < len)
	{
		if (current != NULL)
		{
			if (current->env_var->value
				&& current->env_var->value[0] != '\0')
				printf("%s\n", new_table[i]);
		}
		current = current->next;
		i++;
	}
	shell->error->exit_code = 0;
}

void	ft_env(t_minishell *shell, t_command_list *command_list,
		t_env_list *env)
{
	char		**new_table;
	int			len;

	(void)env;
	new_table = env_list_to_arr(shell, shell->gcn, shell->env_lst);
	len = ft_count_table(new_table);
	if (!command_list->cmd[1])
		print_env(shell, new_table, len);
	else
	{
		print_err_msg("env: ", command_list->cmd[1],
			": No such file or directory\n");
		shell->error->exit_code = 127;
	}
}

int	ft_env_size(t_env_list *list)
{
	int	i;

	i = 0;
	if (!list)
		return (0);
	while (list)
	{
		list = list->next;
		i++;
	}
	return (i);
}

char	**env_list_to_arr(t_minishell *shell, t_garbage_collector *gcn,
		t_env_list *head)
{
	int			i;
	int			env_len;
	char		**cmd_table;
	t_env_list	*current;

	(void)shell;
	i = 0;
	current = head;
	env_len = ft_env_size(current);
	if (!current)
		return (NULL);
	cmd_table = gc_malloc(gcn, sizeof(char *) * (env_len + 1));
	while (current && i < env_len)
	{
		cmd_table[i] = ft_gc_strdup(gcn, current->elem);
		current = current->next;
		i++;
	}
	cmd_table[i] = NULL;
	return (cmd_table);
}
