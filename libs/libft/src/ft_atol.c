/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   ft_atol.c                                          ██╗  ██╗██████╗       */
/*                                                      ██║  ██║╚════██╗      */
/*   By: jupallar <jupallar@student.42.qc>              ███████║ █████╔╝      */
/*                                                      ╚════██║██╔═══╝       */
/*   Created: 2023/02/13 11:45:06 by jupallar                ██║███████╗      */
/*   Updated: 2023/11/30 19:48:47 by jupallar                ╚═╝╚══════╝.qc   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	ft_atol(const char *str)
{
	size_t		i;
	size_t		n;
	long long	r;

	i = 0;
	n = 1;
	r = 0;
	while (str[i] == 32 || str[i] == '\n' || str[i] == '\t' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r')
	{
		i++;
	}
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			n = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		r = (str[i] - 48) + (r * 10);
		i++;
	}
	return ((long long)r * n);
}
