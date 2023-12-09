/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   ft_count_table.c                                   ██╗  ██╗██████╗       */
/*                                                      ██║  ██║╚════██╗      */
/*   By: jupallar <jupallar@student.42.qc>              ███████║ █████╔╝      */
/*                                                      ╚════██║██╔═══╝       */
/*   Created: 2023/10/16 14:14:39 by jupallar                ██║███████╗      */
/*   Updated: 2023/11/18 15:27:32 by jupallar                ╚═╝╚══════╝.qc   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_count_table(char **table)
{
	size_t	i;

	if (!table)
		return (-1);
	i = 0;
	while (table[i] != 0)
		i++;
	return (i);
}