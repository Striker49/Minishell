/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seroy <seroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 17:21:59 by seroy             #+#    #+#             */
/*   Updated: 2023/12/09 16:38:20 by seroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	quote_status(char c, t_quotes *stat)
{
	if (c == '\'')
	{
		if (stat->inside_single_quote == 0 && stat->inside_double_quote == 0)
			stat->inside_single_quote = 1;
		else
			stat->inside_single_quote = 0;
	}
	if (c == '\"')
	{
		if (stat->inside_double_quote == 0 && stat->inside_single_quote == 0)
			stat->inside_double_quote = 1;
		else
			stat->inside_double_quote = 0;
	}
}

char	*if_last_quote(t_minishell *shell, t_token_list *current, 
	t_quotes *stat, int *i)
{
	int		start;
	char	*result;

	start = (*i);
	result = ft_gc_substr(shell->gc, (current)->token.value, 0, start);
	(current)->token.value = ft_gc_strjoin(shell->gc, result,
			ft_gc_substr(shell->gc, (current)->token.value, start + 1,
				(current)->token.len + 1));
	stat->inside_double_quote = 1;
	stat->inside_single_quote = 1;
	return (result);
}

char	*if_valid_var(t_minishell *shell, t_token_list *current, int *i)
{
	int		start;
	char	*result;

	start = (*i);
	(*i)++;
	result = set_variable(shell, &(current), &start, &(*i));
	return (result);
}

int	replace_in_str(t_minishell *shell, t_token_list *current, 
	int *i, t_quotes *stat)
{
	if (current->token.value[*i] == '$' && current->token.value[*i + 1] == '?' 
		&& stat->inside_single_quote == 0)
	{
		(current)->token.value = ft_expand_err(shell, (current), (*i));
		return (1);
	}
	else if ((current)->token.value[(*i)] == '$' && ((current)->token.value[(*i)
				+ 1] == '\"' || (current)->token.value[(*i) + 1] == '\'')
		&& (stat->inside_single_quote != 1 && stat->inside_double_quote != 1))
		if_last_quote(shell, &(*current), stat, &(*i));
	else if ((current)->token.value[(*i)] == '$'
		&& ft_is_valid_var_format((current)->token.value[(*i) + 1])
		&& (stat->inside_double_quote == 1 || stat->inside_single_quote == 0))
	{
		if_valid_var(shell, &(*current), &(*i));
		return (1);
	}
	return (0);
}

void	replace_vars(t_minishell *shell, t_token_list **current)
{
	int			i;
	t_quotes	stat;

	stat.inside_single_quote = 0;
	stat.inside_double_quote = 0;
	i = 0;
	while ((*current)->token.value[i] != '\0')
	{
		quote_status((*current)->token.value[i], &stat);
		if (replace_in_str(shell, &(**current), &i, &stat))
			continue ;
		if ((*current)->token.value[i] != 0)
			i++;
	}
}
