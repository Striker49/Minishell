/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   ft_gc_table_dup.c                                  ██╗  ██╗██████╗       */
/*                                                      ██║  ██║╚════██╗      */
/*   By: jupallar <jupallar@student.42.qc>              ███████║ █████╔╝      */
/*                                                      ╚════██║██╔═══╝       */
/*   Created: 2023/10/16 13:56:42 by jupallar                ██║███████╗      */
/*   Updated: 2023/11/18 15:31:10 by jupallar                ╚═╝╚══════╝.qc   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_gc_table_dup(t_garbage_collector *gc, char **table)
{
	size_t	i;
	size_t	table_len;
	char	**new_table;

	if (!table)
		return (NULL);
	table_len = ft_count_table(table);
	new_table = (char **)gc_malloc(gc, sizeof(char *) * (table_len + 1));
	if (!new_table)
		return (NULL);
	i = 0;
	while (table[i])
	{
		new_table[i] = ft_gc_strdup(gc, table[i]);
		if (!new_table[i])
			return (ft_free_table(new_table));
		i++;
	}
	new_table[i] = NULL;
	return (new_table);
}
