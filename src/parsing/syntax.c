/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   syntax.c                                           ██╗  ██╗██████╗       */
/*                                                      ██║  ██║╚════██╗      */
/*   By: jupallar <jupallar@student.42.qc>              ███████║ █████╔╝      */
/*                                                      ╚════██║██╔═══╝       */
/*   Created: 2023/10/22 23:39:17 by nomu                    ██║███████╗      */
/*   Updated: 2023/12/06 15:16:44 by jupallar                ╚═╝╚══════╝.qc   */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_token_type	ft_is_redir_token(t_token_type current_type)
{
	if (current_type == OUTFILE || current_type == APPEND
		|| current_type == INFILE || current_type == HEREDOC)
		return (current_type);
	return (0);
}

int	validate_redirections(t_token_list *tokens)
{
	t_token_list	*current;

	current = tokens;
	if (ft_is_redir(current->token.type) && current->next == NULL)
		return (0);
	while (current->next)
	{
		if (ft_is_redir(current->token.type)
			&& current->next->token.type != ALPHA)
			return (0);
		current = current->next;
	}
	if (ft_is_redir(current->token.type) && current->next == NULL)
		return (0);
	return (1);
}

int	ft_is_valid_syntax(t_token_list *tokens)
{
	if (!tokens)
		return (0);
	if (!validate_pipes(tokens))
	{
		write(2, "minishell: syntax error near unexpected token `", 47);
		if (ft_count_token_type(tokens, PIPE) % 2 != 0)
			write(2, "|'\n", 3);
		else
			write(2, "||'\n", 4);
		return (0);
	}
	if (!validate_redirections(tokens))
	{
		write(2, "minishell: syntax error near unexpected token `", 47);
		write(2, "newline'\n", 9);
		return (0);
	}
	return (1);
}
