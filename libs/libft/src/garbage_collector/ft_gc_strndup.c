/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   ft_gc_strndup.c                                    ██╗  ██╗██████╗       */
/*                                                      ██║  ██║╚════██╗      */
/*   By: jupallar <jupallar@student.42.qc>              ███████║ █████╔╝      */
/*                                                      ╚════██║██╔═══╝       */
/*   Created: 2023/10/27 23:15:43 by nomu                    ██║███████╗      */
/*   Updated: 2023/11/18 15:30:35 by jupallar                ╚═╝╚══════╝.qc   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_gc_strndup(t_garbage_collector *gc, const char *src, size_t n)
{
	size_t	i;
	size_t	src_len;
	char	*dup;

	src_len = ft_strlen(src);
	if (src_len > n)
		src_len = n;
	dup = gc_malloc(gc, sizeof(char) * (src_len + 1));
	if (!dup)
		return (NULL);
	i = 0;
	while (i < src_len)
	{
		dup[i] = src[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
