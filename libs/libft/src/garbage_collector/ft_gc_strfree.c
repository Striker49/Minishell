/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   ft_gc_strfree.c                                    ██╗  ██╗██████╗       */
/*                                                      ██║  ██║╚════██╗      */
/*   By: jupallar <jupallar@student.42.qc>              ███████║ █████╔╝      */
/*                                                      ╚════██║██╔═══╝       */
/*   Created: 2022/11/04 17:00:42 by jupallar                ██║███████╗      */
/*   Updated: 2023/10/20 13:33:26 by jupallar                ╚═╝╚══════╝.qc   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_gc_strfree(t_garbage_collector *gc, t_string *str)
{
	(void)gc;
	free(str->buffer);
	str->buffer = NULL;
	str->len = 0;
	str->cap = 0;
}
