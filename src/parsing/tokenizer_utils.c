/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   tokenizer_utils.c                                  ██╗  ██╗██████╗       */
/*                                                      ██║  ██║╚════██╗      */
/*   By: jupallar <jupallar@student.42.qc>              ███████║ █████╔╝      */
/*                                                      ╚════██║██╔═══╝       */
/*   Created: 2023/11/12 00:29:09 by jupallar                ██║███████╗      */
/*   Updated: 2023/12/04 13:21:31 by jupallar                ╚═╝╚══════╝.qc   */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_is_delimiter(int c)
{
	if (c == '|' || c == '>' || c == '<')
		return (1);
	return (0);
}

void	ft_init_tk_varaibles(t_minishell *shell, t_tokenizer *tk)
{
	tk->i = 0;
	tk->len = ft_strlen(shell->prompt);
	tk->prompt = shell->prompt;
	tk->head = NULL;
	tk->current = NULL;
	tk->gc = shell->gc;
}

void	handle_double_quotes(t_tokenizer *tk)
{
	tk->i++;
	while (tk->i < tk->len && tk->prompt[tk->i] != '\"')
		tk->i++;
	tk->i++;
}

void	handle_single_quotes(t_tokenizer *tk)
{
	tk->i++;
	while (tk->i < tk->len && tk->prompt[tk->i] != '\'')
		tk->i++;
	tk->i++;
}
