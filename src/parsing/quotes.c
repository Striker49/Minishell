/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   quotes.c                                           ██╗  ██╗██████╗       */
/*                                                      ██║  ██║╚════██╗      */
/*   By: jupallar <jupallar@student.42.qc>              ███████║ █████╔╝      */
/*                                                      ╚════██║██╔═══╝       */
/*   Created: 2023/10/22 19:42:37 by jupallar                ██║███████╗      */
/*   Updated: 2023/11/17 15:06:29 by jupallar                ╚═╝╚══════╝.qc   */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parsing.h"

static void	init_quotes(t_garbage_collector *gc, t_quotes *quotes, char *input)
{
	quotes->i = 0;
	quotes->j = 0;
	quotes->inside_single_quote = 0;
	quotes->inside_double_quote = 0;
	if (!gc || !input)
		return ;
	quotes->len = ft_strlen(input);
	quotes->result = gc_malloc(gc, sizeof(char) * (quotes->len + 1));
}

static void	handle_single_quote(t_quotes *quotes, char current_char)
{
	quotes->inside_single_quote = !quotes->inside_single_quote;
	if (quotes->inside_double_quote)
	{
		quotes->result[quotes->j] = current_char;
		quotes->j++;
	}
}

static void	handle_double_quote(t_quotes *quotes, char current_char)
{
	quotes->inside_double_quote = !quotes->inside_double_quote;
	if (quotes->inside_single_quote)
	{
		quotes->result[quotes->j] = current_char;
		quotes->j++;
	}
}

static void	handle_regular_char(t_quotes *quotes, char current_char)
{
	quotes->result[quotes->j] = current_char;
	quotes->j++;
}

char	*parse_quotes(t_garbage_collector *gc, char *input)
{
	t_quotes	quotes_info;
	char		current_char;

	init_quotes(gc, &quotes_info, input);
	while (input[quotes_info.i] != '\0')
	{
		current_char = input[quotes_info.i];
		if (current_char == '\'' && !quotes_info.inside_double_quote)
			handle_single_quote(&quotes_info, current_char);
		else if (current_char == '\"' && !quotes_info.inside_single_quote)
			handle_double_quote(&quotes_info, current_char);
		else
			handle_regular_char(&quotes_info, current_char);
		quotes_info.i++;
	}
	quotes_info.result[quotes_info.j] = '\0';
	return (quotes_info.result);
}
