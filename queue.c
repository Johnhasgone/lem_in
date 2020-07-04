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

t_room	**get_room(t_queue **room_queue)
{
	int			size;
	t_room 		**return_room;

	size = queue_size(*room_queue);
	if (size == 0)
		return (NULL);
	if (size == 1)
	{
		return_room = (*room_queue)->room;
		free(room_queue);
		room_queue = NULL;
		return (return_room);
	}
	while ((*room_queue)->next->next)
	{
		room_queue = &(*room_queue)->next;
	}
	return_room = (*room_queue)->next->room;
	free((*room_queue)->next);
	(*room_queue)->next = NULL;
	return (return_room);
}