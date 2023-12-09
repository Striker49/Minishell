/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seroy <seroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 16:45:27 by seroy             #+#    #+#             */
/*   Updated: 2023/12/08 19:29:53 by seroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

#define MAX_LINES 100

char	*ft_result_len_hd(t_minishell *shell, char *hd, 
	int *start, int *i)
{
	int		result_len;
	char	*result;
	int		j;

	*start = *i;
	j = (*i) + 1;
	result_len = 0;
	while (ft_isalnum(hd[j])
		|| hd[j] == '_')
	{
		result_len++;
		j++;
	}
	result = ft_gc_substr(shell->gc, hd, *start + 1,
			result_len + 1);
	return (result);
}

char	*set_variable_hd(t_minishell *shell, char *hd, int *start, int *i)
{
	t_var	*variable;
	int		not_var;
	char	*result;

	result = ft_result_len_hd(shell, hd, &(*start), &(*i));
	variable = find_key(result, (ft_strlen(result) - 2), shell->env_lst);
	if (variable)
	{
		if (!variable->value)
			result = "";
		result = ft_gc_substr(shell->gc, hd, 0, *start);
		result = ft_gc_strjoin(shell->gc, result, variable->value);
		result = ft_gc_strjoin(shell->gc, result, &hd[*start
				+ variable->k_len + 1]);
		i = start + variable->v_len - 1;
	}
	else
	{
		not_var = ft_strlen(result) + 1;
		result = ft_gc_substr(shell->gc, hd, 0, *start);
		result = ft_gc_strjoin(shell->gc, result, &hd[*start
				+ not_var]);
		i = start;
	}
	return (hd = result);
}

char	*ft_expand_hd(t_minishell *shell, char *hd)
{
	int		i;
	int		start;
	char	*result;

	if (!hd)
		return (NULL);
	start = 0;
	i = 0;
	while (hd[i])
	{
		if (hd[i] == '$' && hd[i + 1] == '?')
			hd = ft_expand_err_hd(shell, i, hd);
		if (hd[i] == '$' && ft_is_valid_var_format(hd[i + 1]))
		{
			result = set_variable_hd(shell, hd, &start, &i);
			hd = result;
		}
		i++;
	}
	return (hd);
}

void	write_in_hd(int fd, char *tmp)
{
	int	i;

	i = 0;
	while (tmp[i])
	{
		write(fd, &tmp[i], 1);
		i++;
	}
}

t_redir_list	*ft_parse_hd(t_minishell *shell, t_redir_list *redir)
{
	char	*tmp;
	int		i;

	i = 0;
	redir->fd = open(redir->file_name, O_RDWR | O_CREAT);
	if (redir->fd == -1)
		return (perror("open"), NULL);
	tmp = (char *)gc_malloc(shell->gc, MAX_LINES * sizeof(char) + 1);
	if (!tmp)
		return (NULL);
	read(redir->fd, tmp, MAX_LINES);
	if (tmp == NULL)
		return (NULL);
	tmp = ft_expand_hd(shell, tmp);
	ft_close(redir->fd);
	redir->fd = open(redir->file_name, O_RDWR | O_TRUNC | O_CREAT);
	if (redir->fd == -1)
		return (perror("open"), NULL);
	write_in_hd(redir->fd, tmp);
	ft_close(redir->fd);
	return (redir);
}
