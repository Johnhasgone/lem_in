/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cimogene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/04 16:35:18 by cimogene          #+#    #+#             */
/*   Updated: 2020/07/04 16:35:28 by cimogene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		queue_size(t_queue	*room_queue)
{
	int 	size;
	t_queue *start;

	size = 0;
	start = room_queue;
	while (start)
	{
		size++;
		start = start->next;
	}
	return (size);
}

t_queue *create_queue_element(t_room *room)
{
	t_queue *new_queue_elem;

	new_queue_elem = (t_queue*)malloc(sizeof(t_queue));
	if (new_queue_elem != NULL)
	{
		new_queue_elem->room = room;
		new_queue_elem->content_size = sizeof(*room);
		new_queue_elem->next = NULL;
	}
	return new_queue_elem;
}

void put_room(t_queue **room_queue, t_room *room)
{
	t_queue *new_room_node;

	new_room_node = create_queue_element(room);
	ft_lstadd((t_list**) room_queue, (t_list*) new_room_node);
}

t_room	*pop_room(t_queue **room_queue)
{
	return (t_room *) ft_lstpop_end((t_list **) room_queue);
}