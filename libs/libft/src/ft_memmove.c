/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jupallar <jupallar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 17:35:21 by jupallar          #+#    #+#             */
/*   Updated: 2022/05/24 17:25:57 by jupallar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t			i;
	unsigned char	*bloc1;
	unsigned char	*bloc2;

	i = 0;
	bloc1 = (unsigned char *)src;
	bloc2 = (unsigned char *)dst;
	if (!dst && !src)
		return (NULL);
	if (bloc2 > bloc1)
	{
		while (len-- > 0)
			bloc2[len] = bloc1[len];
	}
	else
	{
		while (i < len)
		{
			bloc2[i] = bloc1[i];
			i++;
		}
	}
	return (dst);
}
