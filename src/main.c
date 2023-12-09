/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seroy <seroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 12:52:10 by jupallar          #+#    #+#             */
/*   Updated: 2023/12/08 15:57:06 by seroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <signal.h>

int	main(int argc, char **argv, char **envp)
{
	t_minishell	shell;

	ft_boot_shell(&shell, envp, argc, argv);
	while (1)
	{
		ft_init_loop(&shell, envp);
		ft_process_loop(&shell);
	}
	ft_destroy_shell(&shell);
	return (0);
}
