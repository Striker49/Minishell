/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seroy <seroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 20:43:47 by nomu              #+#    #+#             */
/*   Updated: 2023/12/05 17:41:43 by seroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/print.h"

t_global	g_heredoc;

void	ft_print_tokens(t_token_list *head)
{
	int				i;
	t_token_list	*current;

	i = 0;
	current = head;
	while (current != NULL)
	{
		printf(RED "\nToken index: %d\n" WHITE, i);
		printf(RED "----------\n" WHITE);
		printf("Token value:	%s\n", current->token.value);
		printf("Token len:	%d\n", current->token.len);
		printf("Token type:	%d\n", current->token.type);
		current = current->next;
		i++;
	}
}

void	ft_print_env(t_env_list *head)
{
	int			i;
	t_env_list	*current;

	current = head;
	i = 0;
	while (current != NULL)
	{
		if (i > 1)
		{
			printf(GREEN "Env elem:	%s\n" WHITE, current->prev->prev->elem);
		}
		printf(RED "Env index: %d\n" WHITE, i);
		printf(RED "---------------\n" WHITE);
		printf(PURPLE "Env elem:	%s\n" WHITE, current->elem);
		printf(PINK "Env key:	%s\n" WHITE, current->env_var->key);
		printf(PINK "Env key len:	%d\n" WHITE, current->env_var->k_len);
		printf(MAGENTA "Env value:	%s\n" WHITE, current->env_var->value);
		printf(MAGENTA "Env value len:	%d\n" WHITE, current->env_var->v_len);
		current = current->next;
		i++;
	}
}

void	print_err_msg(const char *prefix, const char *input, const char *suffix)
{
	write(2, prefix, strlen(prefix));
	write(2, input, strlen(input));
	write(2, suffix, strlen(suffix));
}
