/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jupallar <jupallar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 12:54:17 by Juan              #+#    #+#             */
/*   Updated: 2022/05/24 15:15:45 by jupallar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*new;
	t_list	*free;

	if (!lst)
		return ;
	new = *lst;
	while (new)
	{
		free = new;
		new = new->next;
		ft_lstdelone(free, del);
	}
	*lst = 0;
}
