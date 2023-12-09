/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   ft_strcmp.c                                        ██╗  ██╗██████╗       */
/*                                                      ██║  ██║╚════██╗      */
/*   By: jupallar <jupallar@student.42.qc>              ███████║ █████╔╝      */
/*                                                      ╚════██║██╔═══╝       */
/*   Created: 2023/02/25 20:16:38 by jupallar                ██║███████╗      */
/*   Updated: 2023/11/18 15:40:50 by jupallar                ╚═╝╚══════╝.qc   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	index;

	index = 0;
	while (s1[index] || s2[index])
	{
		if (s1[index] != s2[index])
			return (s1[index] - s2[index]);
		else
			index++;
	}
	return (0);
}
