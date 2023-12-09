/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jupallar <jupallar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 16:12:30 by Juan              #+#    #+#             */
/*   Updated: 2022/05/24 15:02:25 by jupallar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*i;
	t_list	*j;

	if (!f)
		return (0);
	i = 0;
	while (lst)
	{
		j = ft_lstnew((*f)(lst->content));
		if (!j)
		{
			ft_lstclear(&i, del);
			return (0);
		}
		ft_lstadd_back(&i, j);
		lst = lst->next;
	}
	return (i);
}
