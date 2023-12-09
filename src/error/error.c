/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seroy <seroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 14:04:38 by seroy             #+#    #+#             */
/*   Updated: 2023/12/01 13:46:49 by seroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	quotes_ntclosed(t_minishell *shell)
{
	write(2, "minishell: syntax error, quotes are not closed `", 48);
	if (count_char(shell->prompt, '\"') % 2 != 0)
		write(2, "\"", 1);
	else if (count_char(shell->prompt, '\'') % 2 != 0)
		write(2, "\'", 1);
	else
	{
		if (ft_strrchr(shell->prompt, '('))
			write(2, "(", 1);
	}
	write(2, "'\n", 2);
	shell->error->exit_code = 2;
}

void	ft_print_error_msg(t_minishell *shell, int flag)
{
	if (flag == 1)
	{
		quotes_ntclosed(shell);
	}
	if (flag == 2)
		shell->error->exit_code = 2;
	if (flag == 3)
	{
		write(2, "minishell: syntax error, near unexpected token `", 48);
		if (ft_strrchr(shell->prompt, ')'))
			write(2, ")", 1);
		else if (ft_strrchr(shell->prompt, '('))
			write(2, "(", 1);
		write(2, "'\n", 2);
		shell->error->exit_code = 2;
	}
	else
		shell->error->exit_code = 1;
}

void	ft_handle_errno(t_minishell *shell, int flag)
{
	char	*error_msg;

	error_msg = NULL;
	shell->error->fd = 2;
	ft_print_error_msg(shell, flag);
	if (!error_msg)
		return ;
}
