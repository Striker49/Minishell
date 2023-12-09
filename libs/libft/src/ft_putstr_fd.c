/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   ft_putstr_fd.c                                     ██╗  ██╗██████╗       */
/*                                                      ██║  ██║╚════██╗      */
/*   By: jupallar <jupallar@student.42.qc>              ███████║ █████╔╝      */
/*                                                      ╚════██║██╔═══╝       */
/*   Created: 2022/04/02 18:41:19 by jupallar                ██║███████╗      */
/*   Updated: 2023/11/03 15:00:58 by jupallar                ╚═╝╚══════╝.qc   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	write(fd, s, ft_strlen(s));
	while (s[i])
	{
		ft_putchar_fd(s[i], fd);
		i++;
	}
}
