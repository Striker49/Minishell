/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seroy <seroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 15:05:08 by jupallar          #+#    #+#             */
/*   Updated: 2023/12/08 19:35:56 by seroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parsing.h"

int	count_char(const char *input, char ch)
{
	int	count;

	count = 0;
	while (*input)
	{
		if (*input == ch)
			count++;
		input++;
	}
	return (count);
}

int	ft_is_valid_quotes(char *string)
{
	int	i;
	int	in_double_quote;
	int	in_single_quote;

	i = 0;
	in_double_quote = 0;
	in_single_quote = 0;
	while (string[i])
	{
		if (string[i] == '\"' && !in_single_quote)
			in_double_quote = !in_double_quote;
		else if (string[i] == '\'' && !in_double_quote)
			in_single_quote = !in_single_quote;
		i++;
	}
	if ((count_char(string, '\(') || count_char(string, ')'))
		&& in_double_quote)
		return (0);
	return (!in_single_quote && !in_double_quote);
}

void	ft_close(int fd)
{
	if (fd > STDERR_FILENO)
		close(fd);
}
