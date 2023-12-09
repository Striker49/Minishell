/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   ft_isdigit.c                                       ██╗  ██╗██████╗       */
/*                                                      ██║  ██║╚════██╗      */
/*   By: jupallar <jupallar@student.42.qc>              ███████║ █████╔╝      */
/*                                                      ╚════██║██╔═══╝       */
/*   Created: 2022/04/07 17:34:48 by jupallar                ██║███████╗      */
/*   Updated: 2023/12/06 20:16:08 by jupallar                ╚═╝╚══════╝.qc   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}