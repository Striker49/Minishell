/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   echo.c                                             ██╗  ██╗██████╗       */
/*                                                      ██║  ██║╚════██╗      */
/*   By: jupallar <jupallar@student.42.qc>              ███████║ █████╔╝      */
/*                                                      ╚════██║██╔═══╝       */
/*   Created: 2023/11/07 11:11:50 by seroy                   ██║███████╗      */
/*   Updated: 2023/11/30 19:50:08 by jupallar                ╚═╝╚══════╝.qc   */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	valid_n(char *option)
{
	int	i;

	i = 2;
	if (ft_strlen(option) < 1)
		return (0);
	if (!ft_strncmp("-n", option, 2))
	{
		while (option[i] && option[i] == 'n')
			i++;
		if (option[i] == '\0')
			return (1);
	}
	return (0);
}

void	ft_echo(t_minishell *shell, t_command_list *command_list)
{
	int	i;

	if (!command_list->cmd[1])
	{
		printf("\n");
		return ;
	}
	if (valid_n(command_list->cmd[1]))
	{
		i = 2;
		while (valid_n(command_list->cmd[i]))
			i++;
	}
	else
		i = 1;
	while (command_list->cmd[i])
	{
		printf("%s", command_list->cmd[i]);
		if (command_list->cmd[i + 1] != NULL)
			printf(" ");
		i++;
	}
	if (!valid_n(command_list->cmd[1]))
		printf("\n");
	shell->error->exit_code = 0;
}
