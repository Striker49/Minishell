/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jupallar <jupallar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 17:35:48 by jupallar          #+#    #+#             */
/*   Updated: 2022/05/24 15:16:58 by jupallar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len1;
	size_t	len2;
	char	*new;

	if (!s1)
		return (0);
	len1 = 0;
	len2 = 0;
	new = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!new)
		return (NULL);
	while (s1[len1] != '\0')
	{
		new[len1] = s1[len1];
		len1++;
	}
	while (s2[len2] != '\0')
	{
		new[len1 + len2] = s2[len2];
		len2++;
	}
	new[len1 + len2] = '\0';
	return (new);
}
