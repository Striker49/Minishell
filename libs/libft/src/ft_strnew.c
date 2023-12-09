/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jupallar <jupallar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 17:03:32 by jupallar          #+#    #+#             */
/*   Updated: 2022/11/07 14:51:29 by jupallar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_string	*ft_strnew(t_string *dst, const char *str)
{
	if (!str)
	{
		dst->buffer = NULL;
		dst->len = 0;
		dst->cap = 0;
	}
	else
	{
		dst->buffer = ft_strdup(str);
		if (!dst->buffer)
			return (NULL);
		dst->len = ft_strlen(str);
		dst->cap = dst->len + 1;
	}
	return (dst);
}
