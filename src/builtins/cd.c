/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seroy <seroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 16:13:24 by seroy             #+#    #+#             */
/*   Updated: 2023/12/08 21:59:29 by seroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include <dirent.h>
#include <limits.h>

int	check_home(t_minishell *shell, t_env_list *env_lst)
{
	t_env_list	*current;
	t_env_list	*home;
	char		*var;

	var = "HOME";
	current = env_lst;
	home = NULL;
	while (current!= NULL)
	{
		if (!ft_strncmp(var, current->env_var->key, 5))
		{
			if (current->env_var->value != NULL)
				home = current;
			else
				return (0);
		}
		current = current->next;
	}
	if (home == NULL || chdir((home->env_var->value)) == -1)
	{
		write(2, "cd: HOME not set\n", 18);
		return (shell->error->exit_code = 1);
	}
	return (0);
}

t_env_list	*update_oldpwd(t_minishell *shell, t_env_list *pwd,
		t_env_list *oldpwd)
{
	oldpwd->env_var->value = pwd->env_var->value;
	oldpwd->env_var->v_len = pwd->env_var->v_len;
	oldpwd->elem = ft_gc_strjoin(shell->gcn, "OLDPWD=", &pwd->elem[4]);
	return (oldpwd);
}

t_env_list	*update_pwd(t_minishell *shell, t_env_list *pwd)
{
	char	buf[PATH_MAX];

	getcwd(buf, PATH_MAX);
	pwd->env_var->value = ft_gc_strdup(shell->gcn, buf);
	pwd->env_var->v_len = ft_strlen(pwd->elem);
	pwd->elem = ft_gc_strjoin(shell->gcn, "PWD=", pwd->env_var->value);
	return (pwd);
}

t_env_list	*find_env_elem(t_minishell *shell, char *var)
{
	t_env_list	*current;

	if (!var)
		return (NULL);
	current = shell->env_lst;
	while (current != NULL)
	{
		if (!ft_strcmp(var, current->env_var->key))
			return (current);
		current = current->next;
	}
	return (NULL);
}

int	ft_cd(t_minishell *shell, t_command_list *command_list)
{
	t_env_list	*pwd;
	t_env_list	*oldpwd;

	if (!command_list->cmd[1])
	{
		if (check_home(shell, shell->env_lst))
			return (1);
	}
	pwd = find_env_elem(shell, "PWD");
	if (pwd != NULL)
	{
		oldpwd = find_env_elem(shell, "OLDPWD");
		if (oldpwd != NULL)
			oldpwd = update_oldpwd(shell, pwd, oldpwd);
	}
	if (command_list->cmd[1] && (chdir(command_list->cmd[1]) == -1))
	{
		print_err_msg("minishell: cd: ", command_list->cmd[1],
			": No such file or directory\n");
		shell->error->exit_code = 1;
		return (1);
	}
	else
		pwd = update_pwd(shell, pwd);
	return (shell->error->exit_code = 0);
}
