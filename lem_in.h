/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cimogene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/26 19:27:15 by cimogene          #+#    #+#             */
/*   Updated: 2019/12/26 19:27:20 by cimogene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
#define LEM_IN_H

# include "libft/libft.h"
# include <string.h>
# include <unistd.h>
# include <stdlib.h>

/* Edge of an ant farm
 * weight: 1, 0, -1 										  //something about the direction of yhe edge
 * from: position of the room in an ant farm (current room) - //or delete this field?
 * to: position of the room current room is connected to
 * */
typedef struct		s_edge
{
	int 			weight;
	int				from;
	int				to;
}					t_edge;

// Node of an ant farm
typedef struct		s_room
{
	char			*name;
	int 			coordinates[2];
	t_list			*edges;
	int				deg;
	int 			type;	// 0 - ordinary, 1 - start, 2 - finish
	int 			way;    // 1 - included in a way for ants, 0 - not included
}					t_room;

// queue for breadth search
typedef struct				s_queue
{
	t_room 					*room;
	size_t 					content_size;
	struct s_queue			*next;
}							t_queue;



int		analyze_room_line(char *line, t_room **farm, int *room_counter, int type);
int		analyze_edge_line(char *line, t_room **farm, int room_counter);
void		set_weight(t_edge **edge, int weight);
t_edge		*create_edge(int from, int to);
void 		put_room(t_queue **room_queue, t_room *room);
t_queue 	*create_queue_element(t_room *room);

#endif
