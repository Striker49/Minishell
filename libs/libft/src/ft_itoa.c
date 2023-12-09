/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jupallar <jupallar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 18:38:47 by jupallar          #+#    #+#             */
/*   Updated: 2022/05/24 15:01:54 by jupallar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_is_negative(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

static int	ft_count_digits(int n)
{
	int	count;

	count = 0;
	if (n <= 0)
		count++;
	while (n != 0)
	{
		count++;
		n = n / 10;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	int		i;
	char	*new;

	i = ft_count_digits(n);
	new = malloc(sizeof(char) * (i + 1));
	if (!new)
		return (NULL);
	new[i] = '\0';
	if (n < 0)
		new[0] = '-';
	else if (n == 0)
		new[0] = '0';
	while (n != 0)
	{
		i--;
		new[i] = ft_is_negative(n % 10) + 48;
		n = n / 10;
	}
	return (new);
}
