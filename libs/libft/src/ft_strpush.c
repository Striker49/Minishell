/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strpush.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jupallar <jupallar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 18:52:23 by jupallar          #+#    #+#             */
/*   Updated: 2022/11/07 17:32:42 by jupallar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_string	*ft_strpush(t_string *dst, char src)
{
	char	str[2];

	str[0] = src;
	str[1] = 0;
	return (ft_strappend(dst, str));
}
