/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seroy <seroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 15:09:48 by jupallar          #+#    #+#             */
/*   Updated: 2023/12/05 17:42:11 by seroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_is_redir(t_token_type type)
{
	return (type == OUTFILE || type == INFILE || type == HEREDOC
		|| type == APPEND);
}

int	ft_count_token_type(t_token_list *head, t_token_type type)
{
	t_token_list	*current;
	int				i;

	if (!head)
		return (0);
	i = 0;
	current = head;
	while (current)
	{
		if (current->token.type == type)
			i++;
		current = current->next;
	}
	return (i);
}

int	validate_pipes(t_token_list *tokens)
{
	t_token_list	*current;

	current = tokens;
	if (current->token.type == PIPE)
		return (0);
	while (current->next)
	{
		if (ft_is_redir(current->token.type) && 
			current->next->token.type == PIPE)
			return (0);
		if (current->token.type == PIPE && current->next->token.type == PIPE)
			return (0);
		current = current->next;
	}
	if (current->token.type == PIPE)
		return (0);
	return (1);
}
