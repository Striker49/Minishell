/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jupallar <jupallar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 17:37:08 by jupallar          #+#    #+#             */
/*   Updated: 2022/05/24 15:17:26 by jupallar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	s1_size;

	i = 0;
	if (!s1)
		return (NULL);
	s1_size = ft_strlen(s1);
	while (s1[i] && ft_strrchr(set, s1[i]))
		i++;
	while (s1_size > i && ft_strrchr(set, s1[s1_size - 1]))
		s1_size--;
	return (ft_substr(s1, i, (s1_size - i)));
}
