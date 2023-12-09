/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seroy <seroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 18:07:50 by seroy             #+#    #+#             */
/*   Updated: 2023/12/08 19:34:40 by seroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_is_valid_var_format(int c)
{
	if (ft_isalnum(c) || c == '_')
		return (1);
	return (0);
}

char	*ft_expand_err(t_minishell *shell, t_token_list *current, int i)
{
	char	*exit_str;
	char	*prefix;
	char	*suffix;
	char	*result;

	exit_str = ft_itoa((int)shell->error->exit_code);
	prefix = ft_gc_substr(shell->gc, current->token.value, 0, i);
	suffix = ft_gc_substr(shell->gc, current->token.value, i + 2,
			ft_strlen(current->token.value) - (i + 2));
	result = ft_gc_strjoin(shell->gc, prefix, exit_str);
	result = ft_gc_strjoin(shell->gc, result, suffix);
	current->token.value = result;
	i += ft_strlen(exit_str) - 1;
	free(exit_str);
	return (result);
}

t_var	*find_key(char *var, int var_len, t_env_list *env_lst)
{
	t_env_list	*current;

	current = env_lst;
	while (current != NULL)
	{
		if (!ft_strncmp(var, current->env_var->key, var_len + 1))
			return (current->env_var);
		current = current->next;
	}
	return (NULL);
}

void	delete_token(t_token_list **tokens, t_token_list **current)
{
	if ((*current) == *tokens)
	{
		(*tokens) = (*current)->next;
		(*current)->prev = NULL;
	}
	else if ((*current)->next != NULL)
	{
		(*current)->prev->next = (*current)->next;
		(*current)->next->prev = (*current)->prev;
	}
	(*current) = (*current)->next;
}

void	ft_find_dollar_sign(t_garbage_collector *gc, t_token_list **tokens,
		t_env_list *env_lst, t_minishell *shell)
{
	t_token_list	*current;

	(void)env_lst;
	current = *tokens;
	while (current != NULL)
	{
		if (current->prev && current->prev->token.type == HEREDOC)
			return ;
		replace_vars(shell, &current);
		if (current->token.value[0] == '\0' || !current)
		{
			delete_token(tokens, &current);
			continue ;
		}
		current->token.value = parse_quotes(gc, current->token.value);
		if (current->token.value[0] == '\0')
			return ;
		current = current->next;
	}
}
