/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jupallar <jupallar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 17:35:50 by jupallar          #+#    #+#             */
/*   Updated: 2022/05/24 15:17:02 by jupallar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	dst_len;
	size_t	src_len;

	src_len = ft_strlen(src);
	dst_len = ft_strlen(dst);
	i = 0;
	j = dst_len;
	if (dstsize <= dst_len)
		return (src_len + dstsize);
	while (src[i] && dst_len < dstsize - 1)
	{
		dst[j] = src[i];
		j++;
		i++;
		dstsize--;
	}
	dst[j] = '\0';
	return (src_len + dst_len);
}
