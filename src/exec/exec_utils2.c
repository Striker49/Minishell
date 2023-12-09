/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   exec_utils2.c                                      ██╗  ██╗██████╗       */
/*                                                      ██║  ██║╚════██╗      */
/*   By: jupallar <jupallar@student.42.qc>              ███████║ █████╔╝      */
/*                                                      ╚════██║██╔═══╝       */
/*   Created: 2023/12/01 16:25:12 by seroy                   ██║███████╗      */
/*   Updated: 2023/12/08 12:55:49 by jupallar                ╚═╝╚══════╝.qc   */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*find_path(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp("PATH=", envp[i], 5))
			return (envp[i]);
		i++;
	}
	return (NULL);
}

char	*ft_strlow(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] >= 65 && str[i] <= 90)
			str[i] += 32;
		i++;
	}
	return (str);
}

int	ft_is_builtin(char *cmd)
{
	char	*temp;

	temp = cmd;
	if (!cmd)
		return (0);
	if (!ft_strncmp("cd", cmd, 2))
		return (1);
	else if (!ft_strncmp("env", ft_strlow(temp), 4))
		return (2);
	else if (!ft_strncmp("export", cmd, 6))
		return (3);
	if (!ft_strncmp("pwd", ft_strlow(temp), 4))
		return (4);
	if (!ft_strncmp("unset", cmd, 6))
		return (5);
	if (!ft_strncmp("echo", ft_strlow(temp), 6))
		return (6);
	if (!ft_strncmp("exit", cmd, 5))
		return (7);
	else
		return (0);
}

void	ft_exec_builtin(t_minishell *shell, int flag,
		t_command_list *cmd_cursor)
{
	if (flag == 1)
		ft_cd(shell, cmd_cursor);
	else if (flag == 2)
		ft_env(shell, cmd_cursor, shell->env_lst);
	else if (flag == 3)
		ft_export(shell, shell->envp);
	else if (flag == 4)
		ft_pwd(shell);
	else if (flag == 5)
		ft_unset(shell, shell->exec->command_list);
	else if (flag == 6)
		ft_echo(shell, cmd_cursor);
	else if (flag == 7)
		ft_exit(shell, cmd_cursor);
}
