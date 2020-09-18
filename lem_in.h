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

typedef enum		e_type
{
	SIMPLE,
	START,
	END,
	DUPLICATE
}					e_room_type;

// Node of an ant farm
typedef struct		s_room
{
	char			 *name;
	int 			 coordinates[2];
	t_list			 *edges;
	int				 deg;
	e_room_type		 type;	// 0 - ordinary, 1 - start, 2 - finish, 3 - duplicated    USE ENUM FOR TYPES OF ROOMS (check the Norm)
	int 			dist;
	int 			 way;    // 1 - included in a way for ants, 0 - not included
}					 t_room;

// queue for breadth search
typedef struct				s_queue
{
	t_room 					*room;
	size_t 					content_size;
	struct s_queue			*next;
}							t_queue;



int							analyze_room_line(char *line, t_room **farm, int *room_counter, int type);
int							analyze_edge_line(char *line, t_room **farm, int room_counter);
void						set_weight(t_edge **edge, int weight);
t_edge						*create_edge(int from, int to);
void 						put_room(t_queue **room_queue, t_room *room);
t_queue 					*create_queue_element(t_room *room);
void 						write_ant_moving(t_list *shortest_path_list);
t_list 						*find_shortest_paths(t_room **farm, int *room_counter);
void 						free_current_farm(t_room **current_farm);
void 						add_zero_edge(t_room **farm, int from, int to, int weight);
t_edge						*edge_copy(t_edge *edge);
void 						seek_and_negate_edge(t_list **edge_list, int from, int to);
void 						seek_and_destroy_edge(t_list **edge_list, int from, int to);
int							get_max_path_count(t_room *farm);
int							ft_lst_length(t_list *list);
void						ft_farm_copy(t_room **farm, t_room **current_farm);
void						initialize_current_farm(t_room **current_farm);
void						reverse_shortest_paths(t_room **current_farm, t_list *shortest_path);
void						remove_edges_to_out(t_room **current_farm, int out);
void						remove_edges_from_in(t_room **room_in);

#endif
