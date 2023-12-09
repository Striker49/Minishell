/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jupallar <jupallar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 18:42:19 by jupallar          #+#    #+#             */
/*   Updated: 2022/04/07 19:12:10 by jupallar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*str1;
	unsigned char	*str2;

	i = 0;
	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	if (i == n)
		return (0);
	while (i < (n - 1) && str1[i] == str2[i] && str1[i] != '\0')
		i++;
	if (str1[i] != str2[i])
		return ((unsigned char)str1[i] - (unsigned char)str2[i]);
	return (0);
}
