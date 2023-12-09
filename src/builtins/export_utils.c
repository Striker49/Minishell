/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seroy <seroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 13:25:45 by jupallar          #+#    #+#             */
/*   Updated: 2023/12/04 16:00:26 by seroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*quote_substring(t_garbage_collector *gcn, char *input)
{
	char	*equal_sign;
	int		index;
	char	*new_input;
	size_t	new_length;

	equal_sign = ft_strchr(input, '=');
	if (equal_sign != NULL)
	{
		index = (int)(equal_sign - input);
		new_length = ft_strlen(input) + 3;
		new_input = gc_malloc(gcn, new_length);
		if (!new_input)
		{
			perror("Unable to allocate memory");
			exit(EXIT_FAILURE);
		}
		ft_memmove(new_input, input, index + 1);
		new_input[index + 1] = '\"';
		ft_memmove(new_input + index + 2, equal_sign + 1, ft_strlen(equal_sign
				+ 1) + 1);
		ft_strlcat(new_input, "\"", new_length);
		return (new_input);
	}
	return (ft_gc_strdup(gcn, input));
}

void	print_table(char **arr, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		printf("%s\n", arr[i]);
		i++;
	}
}

char	**sort_string_tab(char **tab, unsigned int size)
{
	unsigned int	i;
	char			*temp;

	i = 0;
	if (size < 2)
	{
		return (tab);
	}
	while (i < size - 1)
	{
		if (ft_strcmp(tab[i], tab[i + 1]) > 0)
		{
			temp = tab[i];
			tab[i] = tab[i + 1];
			tab[i + 1] = temp;
			i = 0;
		}
		else
			i++;
	}
	return (tab);
}

int	ft_is_valid_export_var(t_minishell *shell, char *string)
{
	int	i;

	i = 0;
	if (string[0] == '-')
	{
		print_err_msg("export: usage: option not supported `", string, "'\n");
		return (0);
	}
	if (ft_isalpha(string[0]) || string[0] == '_' || string[0] == '-')
		i++;
	else
	{
		print_err_msg("minishell: export: `", string,
			"': not a valid identifier\n");
		shell->error->exit_code = 1;
		return (0);
	}
	while (ft_isalnum(string[i]) || string[i] == '_')
		i++;
	if (string[i] == '=' || string[i] == '\0')
		return (1);
	shell->error->exit_code = 1;
	print_err_msg("minishell: export: `", string,
		"': not a valid identifier\n");
	return (0);
}

int	print_all_vars(t_minishell *shell, char **envp, t_token_list *current)
{
	int		i;
	char	**table;
	int		len;

	table = env_list_to_arr(shell, shell->gcn, shell->env_lst);
	if (current->len == 1)
	{
		len = ft_count_table(shell->envp);
		table = sort_string_tab(envp, len);
		i = 0;
		while (table[i])
		{
			table[i] = ft_gc_strjoin(shell->gcn, "declare -x ", table[i]);
			table[i] = quote_substring(shell->gcn, table[i]);
			i++;
		}
		print_table(table, len);
		shell->error->exit_code = 0;
		return (1);
	}
	else
		return (0);
}
