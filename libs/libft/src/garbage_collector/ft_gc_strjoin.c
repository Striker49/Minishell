/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   ft_gc_strjoin.c                                    ██╗  ██╗██████╗       */
/*                                                      ██║  ██║╚════██╗      */
/*   By: jupallar <jupallar@student.42.qc>              ███████║ █████╔╝      */
/*                                                      ╚════██║██╔═══╝       */
/*   Created: 2023/10/24 16:01:44 by jupallar                ██║███████╗      */
/*   Updated: 2023/11/18 15:31:48 by jupallar                ╚═╝╚══════╝.qc   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_gc_strjoin(t_garbage_collector *gc, char const *s1, char const *s2)
{
	char	*new_str;
	size_t	i;
	size_t	j;
	size_t	new_len;

	i = ft_strlen(s1);
	j = ft_strlen(s2);
	new_len = ft_strlen(s1) + ft_strlen(s2);
	if (!s1 || !s2)
		return (NULL);
	new_str = gc_malloc(gc, sizeof(char) * (new_len + 1));
	if (!new_str)
		return (NULL);
	ft_strlcpy(new_str, s1, i + 1);
	ft_strlcpy(new_str + i, s2, j + 1);
	return (new_str);
}
