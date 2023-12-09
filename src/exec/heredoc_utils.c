/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seroy <seroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 13:10:12 by jupallar          #+#    #+#             */
/*   Updated: 2023/12/08 19:31:05 by seroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/exec.h"
#include "../../inc/minishell.h"
#include <signal.h>

t_global		g_heredoc;

char	*ft_expand_err_hd(t_minishell *shell, int i, char *hd)
{
	char	*exit_str;
	char	*prefix;
	char	*suffix;
	char	*result;

	exit_str = ft_itoa((int)shell->error->exit_code);
	prefix = ft_gc_substr(shell->gc, hd, 0, i);
	suffix = ft_gc_substr(shell->gc, hd, i + 2, ft_strlen(hd) - (i + 2));
	result = ft_gc_strjoin(shell->gc, prefix, exit_str);
	result = ft_gc_strjoin(shell->gc, result, suffix);
	hd = result;
	i += ft_strlen(exit_str) - 1;
	free(exit_str);
	return (result);
}

void	free_hd(int s)
{
	ft_close(g_heredoc.fd);
	free(g_heredoc.delimiter);
	if (s == 0)
		exit(0);
	if (s == 1)
		exit(1);
}

void	forked_hd(void)
{
	while (1 && g_heredoc.fd)
	{
		g_heredoc.line = readline("> ");
		if (!g_heredoc.line)
		{
			free_hd(1);
			return ;
		}
		if (ft_strcmp(g_heredoc.line, g_heredoc.delimiter) != 0)
		{
			if (write(g_heredoc.fd, g_heredoc.line,
					ft_strlen(g_heredoc.line)) < 0 || write(g_heredoc.fd, "\n",
					1) < 0)
			{
				perror("write");
				free_hd(1);
			}
		}
		else
		{
			write(g_heredoc.fd, "\0", 1);
			free_hd(0);
		}
	}
}

t_redir_list	*setup_hd(t_minishell *shell, t_redir_list *redir)
{
	g_heredoc.shell = shell;
	g_heredoc.line = NULL;
	if (!ft_strchr(redir->file_name, '\"') && !ft_strchr(redir->file_name,
			'\''))
		redir->hd_parse = 1;
	redir->file_name = parse_quotes(shell->gc, redir->file_name);
	redir->delimiter = parse_quotes(shell->gc, redir->delimiter);
	redir->file_name = ft_gc_strjoin(shell->gc, "/tmp/", redir->file_name);
	redir->fd = open(redir->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (redir->fd == -1)
		perror("open");
	g_heredoc.fd = redir->fd;
	g_heredoc.delimiter = ft_strdup(redir->delimiter);
	g_heredoc.child = 2;
	return (redir);
}

int	handle_heredoc(t_minishell *shell, t_redir_list *redir)
{
	pid_t	pid;
	int		status;

	redir = setup_hd(shell, redir);
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, &interrupt_hd);
		gc_collect(shell->gc);
		gc_collect(shell->gcn);
		forked_hd();
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status) == 1)
		if (status == 256)
			return (exit_hd(shell), 1);
	g_heredoc.child = 0;
	free_hd(2);
	if (redir->hd_parse == 1 && g_heredoc.stop == 0)
		redir = ft_parse_hd(shell, redir);
	ft_close(redir->fd);
	return (0);
}
