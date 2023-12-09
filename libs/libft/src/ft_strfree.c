/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strfree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jupallar <jupallar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 17:00:42 by jupallar          #+#    #+#             */
/*   Updated: 2022/11/07 17:29:23 by jupallar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strfree(t_string *str)
{
	free(str->buffer);
	str->buffer = NULL;
	str->len = 0;
	str->cap = 0;
}
