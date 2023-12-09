/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seroy <seroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 14:39:40 by seroy             #+#    #+#             */
/*   Updated: 2023/12/08 21:54:07 by seroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_global	g_heredoc;

void	interrupt(int sig)
{
	(void)sig;
	if (g_heredoc.child == 1)
		return ;
	if (g_heredoc.child == 2)
	{
		g_heredoc.stop = 1;
		return ;
	}
	else
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	interrupt_hd(int sig)
{
	(void)sig;
	ft_close(g_heredoc.fd);
	free(g_heredoc.line);
	free(g_heredoc.delimiter);
	g_heredoc.delimiter = NULL;
	g_heredoc.stop = 1;
	exit(1);
}

void	do_nothing(int sig)
{
	(void)sig;
	printf("do nothing\n");
}

void	deactivate_ctrl(struct termios original_term)
{
	struct termios	t;

	t = original_term;
	t.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &t);
}

void	reactivate_ctrl(void)
{
	struct termios	term;

	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}
