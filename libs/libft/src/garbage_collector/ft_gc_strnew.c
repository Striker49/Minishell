/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   ft_gc_strnew.c                                     ██╗  ██╗██████╗       */
/*                                                      ██║  ██║╚════██╗      */
/*   By: jupallar <jupallar@student.42.qc>              ███████║ █████╔╝      */
/*                                                      ╚════██║██╔═══╝       */
/*   Created: 2022/11/04 17:03:32 by jupallar                ██║███████╗      */
/*   Updated: 2023/11/18 15:30:41 by jupallar                ╚═╝╚══════╝.qc   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_string	*ft_gc_strnew(t_garbage_collector *gc, t_string *dst,
		const char *str)
{
	if (!str)
	{
		dst->buffer = NULL;
		dst->len = 0;
		dst->cap = 0;
	}
	else
	{
		dst->buffer = ft_gc_strdup(gc, str);
		if (!dst->buffer)
			return (NULL);
		dst->len = ft_strlen(str);
		dst->cap = dst->len + 1;
	}
	return (dst);
}
