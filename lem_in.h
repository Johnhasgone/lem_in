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

#define ROOM_NUM 10000

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

typedef enum e_room_type
{
	SIMPLE,
	START,
	END,
	DUPLICATE
};

// Node of an ant farm
typedef struct		s_room
{
	char			 *name;
	int 			 coordinates[2];
	t_list			 *edges;
	int				 deg;
	enum e_room_type type;	// 0 - ordinary, 1 - start, 2 - finish, 3 - duplicated    USE ENUM FOR TYPES OF ROOMS (check the Norm)
	int 			 way;    // 1 - included in a way for ants, 0 - not included
}					 t_room;

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
void 		write_ant_moving(t_list *shortest_path_list);
t_list *find_shortest_paths(t_room **farm, int *room_counter);
void free_current_farm(t_room **current_farm);

#endif
