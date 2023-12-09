/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seroy <seroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 19:27:20 by seroy             #+#    #+#             */
/*   Updated: 2023/12/01 14:39:39 by seroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_strisdigit(char *str)
{
	long long	i;

	i = 0;
	while (str[i])
	{
		if (str[0] == '-' || str[0] == '+')
			i++;
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	if (ft_strlen(str) >= 19 && ft_strcmp(str, "9223372036854775808") >= 0)
		return (0);
	if (ft_strlen(str) >= 20 && ft_strcmp(str, "-9223372036854775809") >= 0)
		return (0);
	return (1);
}

int	ft_exit(t_minishell *shell, t_command_list *command_list)
{
	if (command_list->cmd[1])
	{
		if (ft_count_table(command_list->cmd) > 2)
		{
			write(2, "minishell: exit: too many arguments\n", 37);
			return (shell->error->exit_code = 1);
		}
		else if (!ft_strisdigit(command_list->cmd[1]))
		{
			write(2, "minishell: exit: ", 18);
			write(2, command_list->cmd[1], ft_strlen(command_list->cmd[1]));
			write(2, ": numeric argument required\n", 29);
			shell->error->exit_code = 255;
			ft_destroy_shell(shell);
		}
	}
	if (command_list->cmd[1])
		shell->error->exit_code = ft_atoi(command_list->cmd[1]);
	ft_destroy_shell(shell);
	return (0);
}
