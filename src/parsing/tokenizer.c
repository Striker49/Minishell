/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seroy <seroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 03:32:21 by nomu              #+#    #+#             */
/*   Updated: 2023/11/14 12:03:25 by seroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_token_list	*new_token_node(t_tokenizer *tk, t_token token)
{
	t_token_list	*new_node;

	new_node = gc_malloc(tk->gc, sizeof(t_token_list));
	if (!new_node)
		return (NULL);
	new_node->token = token;
	new_node->next = NULL;
	new_node->prev = NULL;
	return (new_node);
}

void	add_token_to_list(t_tokenizer *tk, t_token token)
{
	if (!tk->head)
	{
		tk->head = new_token_node(tk, token);
		tk->current = tk->head;
	}
	else
	{
		tk->current->next = new_token_node(tk, token);
		tk->current->next->prev = tk->current;
		tk->current = tk->current->next;
	}
}

void	handle_delimiter(t_tokenizer *tk)
{
	size_t	start;

	start = tk->i;
	if (tk->prompt[tk->i] == '|')
		handle_pipe_token(tk);
	else
	{
		if (tk->prompt[tk->i] == '>' && tk->prompt[tk->i + 1] == '>')
			handle_append_token(tk, start);
		else if (tk->prompt[tk->i] == '<' && tk->prompt[tk->i + 1] == '<')
			handle_heredoc_token(tk, start);
		else if (tk->prompt[tk->i] == '>')
			handle_outfile_token(tk, start);
		else
			handle_infile_token(tk, start);
	}
}

void	handle_alpha(t_tokenizer *tk)
{
	size_t	start;
	t_token	token;

	start = tk->i;
	while (tk->i < tk->len && !ft_is_delimiter(tk->prompt[tk->i])
		&& !ft_isspace(tk->prompt[tk->i]))
	{
		if (tk->prompt[tk->i] == '\"')
			handle_double_quotes(tk);
		else if (tk->prompt[tk->i] == '\'')
			handle_single_quotes(tk);
		else
			tk->i++;
	}
	token = ft_build_token(tk, tk->prompt + start, tk->i - start, ALPHA);
	add_token_to_list(tk, token);
}

t_token_list	*tokenizer(t_minishell *shell, char *prompt)
{
	t_tokenizer	tk;

	ft_init_tk_varaibles(shell, &tk);
	if (!prompt || !ft_validate_quotes(shell, shell->prompt))
		return (NULL);
	while (tk.prompt[tk.i])
	{
		while (ft_isspace(tk.prompt[tk.i]))
			tk.i++;
		if (ft_is_delimiter(tk.prompt[tk.i]))
			handle_delimiter(&tk);
		else if (tk.i < tk.len)
			handle_alpha(&tk);
	}
	return (tk.head);
}
