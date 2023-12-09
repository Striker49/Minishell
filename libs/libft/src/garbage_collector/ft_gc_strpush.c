/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   ft_gc_strpush.c                                    ██╗  ██╗██████╗       */
/*                                                      ██║  ██║╚════██╗      */
/*   By: jupallar <jupallar@student.42.qc>              ███████║ █████╔╝      */
/*                                                      ╚════██║██╔═══╝       */
/*   Created: 2022/11/04 18:52:23 by jupallar                ██║███████╗      */
/*   Updated: 2023/10/18 17:51:36 by jupallar                ╚═╝╚══════╝.qc   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_string	*ft_gc_strpush(t_garbage_collector *gc, t_string *dst, char src)
{
	char	str[2];

	str[0] = src;
	str[1] = 0;
	return (ft_gc_strappend(gc, dst, str));
}
