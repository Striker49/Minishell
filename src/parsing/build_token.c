/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   build_token.c                                      ██╗  ██╗██████╗       */
/*                                                      ██║  ██║╚════██╗      */
/*   By: jupallar <jupallar@student.42.qc>              ███████║ █████╔╝      */
/*                                                      ╚════██║██╔═══╝       */
/*   Created: 2023/11/13 15:48:09 by jupallar                ██║███████╗      */
/*   Updated: 2023/12/01 15:04:09 by jupallar                ╚═╝╚══════╝.qc   */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_hd_quotes(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\"' || str[i] == '\'')
			return (1);
		i++;
	}
	return (0);
}

t_token	ft_build_token(t_tokenizer *tk, char *start, size_t len,
		t_token_type type)
{
	t_token	new_token;

	new_token.value = gc_malloc(tk->gc, sizeof(char) * len + 1);
	if (!new_token.value)
	{
		new_token.type = ERROR;
		return (new_token);
	}
	ft_strlcpy(new_token.value, start, len + 1);
	new_token.value[len] = '\0';
	new_token.type = type;
	new_token.len = len;
	if (ft_hd_quotes(new_token.value))
		new_token.expand_hd = 1;
	else
		new_token.expand_hd = 0;
	return (new_token);
}
