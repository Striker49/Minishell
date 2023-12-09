/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seroy <seroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 17:21:53 by seroy             #+#    #+#             */
/*   Updated: 2023/12/05 18:22:14 by seroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*ft_result_len(t_minishell *shell, t_token_list **current, 
	int *start, int *i)
{
	int		result_len;
	char	*result;

	result_len = 0;
	while (ft_isalnum((*current)->token.value[(*i)])
		|| (*current)->token.value[(*i)] == '_')
	{
		result_len++;
		(*i)++;
	}
	result = ft_gc_substr(shell->gc, (*current)->token.value, *start + 1,
			result_len);
	return (result);
}

char	*set_variable(t_minishell *shell, t_token_list **current, 
	int *start, int *i)
{
	t_var	*variable;
	int		not_var;
	char	*result;

	result = ft_result_len(shell, &(*current), &(*start), &(*i));
	variable = find_key(result, ft_strlen(result), shell->env_lst);
	if (variable && variable->value)
	{
		if (!variable->value)
			result = "";
		result = ft_gc_substr(shell->gc, (*current)->token.value, 0, *start);
		result = ft_gc_strjoin(shell->gc, result, variable->value);
		result = ft_gc_strjoin(shell->gc, result,
				&(*current)->token.value[*start + variable->k_len + 1]);
		*i = *start + variable->v_len - 1;
	}
	else
	{
		not_var = ft_strlen(result) + 1;
		result = ft_gc_substr(shell->gc, (*current)->token.value, 0, *start);
		result = ft_gc_strjoin(shell->gc, result,
				&(*current)->token.value[*start + not_var]);
		*i = *start;
	}
	return ((*current)->token.value = result);
}
