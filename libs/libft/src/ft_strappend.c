/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strappend.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jupallar <jupallar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 17:17:15 by jupallar          #+#    #+#             */
/*   Updated: 2022/11/07 17:31:05 by jupallar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	increase_buffer(t_string *str, size_t new_cap)
{
	char	*tmp;

	if (new_cap < str->cap * 2)
		new_cap = str->cap * 2;
	tmp = malloc(sizeof(char) * new_cap);
	if (!tmp)
		return (0);
	if (str->buffer)
		ft_memcpy(tmp, str->buffer, str->len + 1);
	else
		*tmp = 0;
	free(str->buffer);
	str->cap = new_cap;
	str->buffer = tmp;
	return (1);
}

t_string	*ft_strappend(t_string *dst, const char *src)
{
	size_t	src_len;

	src_len = ft_strlen(src);
	if (src_len + dst->len >= dst->cap)
	{
		if (!increase_buffer(dst, dst->len + src_len + 1))
			return (NULL);
	}
	ft_strlcat(dst->buffer, src, dst->cap);
	dst->len += src_len;
	return (dst);
}
