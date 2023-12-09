/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   ft_gc_strdup.c                                     ██╗  ██╗██████╗       */
/*                                                      ██║  ██║╚════██╗      */
/*   By: jupallar <jupallar@student.42.qc>              ███████║ █████╔╝      */
/*                                                      ╚════██║██╔═══╝       */
/*   Created: 2023/10/18 16:55:59 by jupallar                ██║███████╗      */
/*   Updated: 2023/11/18 15:41:18 by jupallar                ╚═╝╚══════╝.qc   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_gc_strdup(t_garbage_collector *gc, const char *src)
{
	int		i;
	int		size;
	char	*dup;

	size = 0;
	while (src[size])
	{
		size++;
	}
	dup = gc_malloc(gc, sizeof(char) * (size + 1));
	if (!dup)
		return (NULL);
	i = 0;
	while (src[i] != '\0')
	{
		dup[i] = src[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
