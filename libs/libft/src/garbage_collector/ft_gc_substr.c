/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   ft_gc_substr.c                                     ██╗  ██╗██████╗       */
/*                                                      ██║  ██║╚════██╗      */
/*   By: jupallar <jupallar@student.42.qc>              ███████║ █████╔╝      */
/*                                                      ╚════██║██╔═══╝       */
/*   Created: 2023/10/28 14:18:25 by jupallar                ██║███████╗      */
/*   Updated: 2023/11/18 15:42:27 by jupallar                ╚═╝╚══════╝.qc   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_gc_substr(t_garbage_collector *gc, char const *s,
		unsigned int start, size_t len)
{
	size_t	i;
	char	*new_str;

	i = 0;
	if (!s)
		return (0);
	if (start > ft_strlen(s))
		start = ft_strlen(s);
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	new_str = gc_malloc(gc, sizeof(char) * len + 1);
	if (!new_str)
		return (NULL);
	while (i < len)
	{
		new_str[i] = s[start + i];
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}
