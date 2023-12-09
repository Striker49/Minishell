/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   ft_split.c                                         ██╗  ██╗██████╗       */
/*                                                      ██║  ██║╚════██╗      */
/*   By: jupallar <jupallar@student.42.qc>              ███████║ █████╔╝      */
/*                                                      ╚════██║██╔═══╝       */
/*   Created: 2022/04/12 22:43:50 by Juan                    ██║███████╗      */
/*   Updated: 2023/11/18 15:29:59 by jupallar                ╚═╝╚══════╝.qc   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	ft_count_strs(const char *s, char c)
{
	unsigned int	i;
	unsigned int	count;
	char			last;

	i = 0;
	count = 0;
	last = c;
	while (s && s[i] != '\0')
	{
		if (s[i] != c && last == c)
			count++;
		last = s[i];
		i++;
	}
	return (count);
}

static unsigned int	ft_strslen(char **str, unsigned int *str_len, char c)
{
	unsigned int	i;

	*str += *str_len;
	*str_len = 0;
	i = 0;
	while (**str && **str == c)
		(*str)++;
	while ((*str)[i])
	{
		if ((*str)[i] == c)
			return (i);
		i++;
	}
	return (i);
}

char	**ft_split(char const *s, char c)
{
	char			**tab;
	char			*str;
	unsigned int	str_len;
	unsigned int	str_count;
	unsigned int	i;

	i = 0;
	str = (char *)s;
	str_len = 0;
	str_count = ft_count_strs(s, c);
	tab = (char **)malloc(sizeof(char *) * (str_count + 1));
	if (!s || !tab)
		return (NULL);
	while (i < str_count)
	{
		str_len = ft_strslen(&str, &str_len, c);
		tab[i] = malloc(sizeof(char) * (str_len + 1));
		if (!tab[i])
			return (ft_free_table(tab));
		ft_strlcpy(tab[i], str, str_len + 1);
		i++;
	}
	tab[i] = NULL;
	return (tab);
}
