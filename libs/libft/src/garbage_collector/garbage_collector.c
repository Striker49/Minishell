/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   garbage_collector.c                                ██╗  ██╗██████╗       */
/*                                                      ██║  ██║╚════██╗      */
/*   By: jupallar <jupallar@student.42.qc>              ███████║ █████╔╝      */
/*                                                      ╚════██║██╔═══╝       */
/*   Created: 2023/09/20 16:42:11 by nomu                    ██║███████╗      */
/*   Updated: 2023/10/20 13:43:05 by jupallar                ╚═╝╚══════╝.qc   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_garbage_collector	*init_garbage_collector(void)
{
	t_garbage_collector	*gc;

	gc = (t_garbage_collector *)malloc(sizeof(t_garbage_collector));
	if (gc)
	{
		gc->head = NULL;
	}
	return (gc);
}

void	*gc_malloc(t_garbage_collector *gc, size_t size)
{
	void				*ptr;
	t_memory_addresses	*new_node;

	if (!gc)
		return (NULL);
	ptr = malloc(size);
	if (!ptr)
		return (NULL);
	new_node = (t_memory_addresses *)malloc(sizeof(t_memory_addresses));
	if (!new_node)
	{
		free(ptr);
		return (NULL);
	}
	new_node->data = ptr;
	new_node->next = gc->head;
	gc->head = new_node;
	return (ptr);
}

void	gc_collect_address(t_garbage_collector *gc, void *address)
{
	t_memory_addresses	*current;
	t_memory_addresses	*previous;

	if (!gc || !gc->head)
		return ;
	current = gc->head;
	previous = NULL;
	while (current)
	{
		if (current->data == address)
		{
			if (previous == NULL)
				gc->head = current->next;
			else
				previous->next = current->next;
			free(current->data);
			free(current);
			return ;
		}
		previous = current;
		current = current->next;
	}
}

void	gc_collect(t_garbage_collector *gc)
{
	t_memory_addresses	*current;
	t_memory_addresses	*temp;

	if (!gc)
		return ;
	current = gc->head;
	while (current)
	{
		temp = current;
		current = current->next;
		free(temp->data);
		free(temp);
	}
	gc->head = NULL;
	free(gc);
}
