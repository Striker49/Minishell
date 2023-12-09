/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   token_handlers.c                                   ██╗  ██╗██████╗       */
/*                                                      ██║  ██║╚════██╗      */
/*   By: jupallar <jupallar@student.42.qc>              ███████║ █████╔╝      */
/*                                                      ╚════██║██╔═══╝       */
/*   Created: 2023/11/12 01:42:31 by jupallar                ██║███████╗      */
/*   Updated: 2023/12/01 15:07:52 by jupallar                ╚═╝╚══════╝.qc   */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	handle_pipe_token(t_tokenizer *tk)
{
	t_token	token;

	token = ft_build_token(tk, tk->prompt + tk->i, 1, PIPE);
	tk->i++;
	add_token_to_list(tk, token);
}

void	handle_append_token(t_tokenizer *tk, size_t start)
{
	t_token	token;

	tk->i += 2;
	token = ft_build_token(tk, tk->prompt + start, tk->i - start, APPEND);
	add_token_to_list(tk, token);
}

void	handle_heredoc_token(t_tokenizer *tk, size_t start)
{
	t_token	token;

	tk->i += 2;
	token = ft_build_token(tk, tk->prompt + start, tk->i - start, HEREDOC);
	add_token_to_list(tk, token);
}

void	handle_outfile_token(t_tokenizer *tk, size_t start)
{
	t_token	token;

	tk->i++;
	token = ft_build_token(tk, tk->prompt + start, tk->i - start, OUTFILE);
	add_token_to_list(tk, token);
}

void	handle_infile_token(t_tokenizer *tk, size_t start)
{
	t_token	token;

	tk->i++;
	token = ft_build_token(tk, tk->prompt + start, tk->i - start, INFILE);
	add_token_to_list(tk, token);
}
