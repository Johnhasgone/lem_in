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
	char			*name;
	int				coordinates[2];
	t_list			*out_edges;
	t_list			*in_edges;
	e_room_type		type;	// 0 - ordinary, 1 - start, 2 - finish, 3 - duplicated    USE ENUM FOR TYPES OF ROOMS (check the Norm)
	int 			dist;
	int 			way;    // 1 - included in a way for ants, 0 - not included
}					t_room;

// queue for breadth search
typedef struct				s_queue
{
	t_room 					*room;
	size_t 					content_size;
	struct s_queue			*next;
}							t_queue;



int							analyze_room_line(char *line, t_room **farm, int *room_counter, int type);
int							analyze_edge_line(char *line, t_room **farm, int room_counter);
t_edge *create_edge(int from, int to, int weight);
void 						put_room(t_queue **room_queue, t_room *room);
t_queue 					*create_queue_element(t_room *room);
void write_ant_moving(t_list *shortest_path_list, int ants, int effectiveness);
t_list *find_shortest_paths(t_room **farm, int *room_counter, int ants,
							int *effectiveness);
void 						free_current_farm(t_room **current_farm);
void 						add_zero_edge(t_room **farm, int from, int to, int weight);
t_edge						*edge_copy(t_edge *edge);
void 						 seek_and_negate_edge(t_list **edge_list, int from, int to);
void 						seek_and_destroy_edge(t_list **edge_list, int from, int to);
int							get_max_path_count(t_room **farm, int room_counter);
int							ft_lst_length(t_list *list);
void						ft_farm_copy(t_room **farm, t_room **current_farm);
void						initialize_current_farm(t_room **current_farm);
void						reverse_shortest_paths(t_room **current_farm, t_list *shortest_path);
void						remove_edges_from_in(t_room **room_in);
t_list						*get_shortest_path_before_collapse(t_room **farm, int room_counter);
void						bellman_ford_algo(t_room **farm, int room_counter);
void fill_shortest_path(t_room **farm, int room_number, t_list **shortest_path,
						int counter);
void 						delete_zero_edge(t_list **shortest_path);
void						delete_bilateral_edges(t_list *shortest_path, t_list **shortest_path_list);
int							check_for_connected_graph(t_room **farm, int room_counter);
t_list						*collapse_shortest_path(t_room **farm, t_list *shortest_path);
int							get_effectiveness_of_shortest_path_list(
		t_list *shortest_path_list, int ants, int iter, t_room **farm);
int							get_path_length(t_list *shortest_path_list, int to, t_room **farm);
int							find_min_length(const int *path_length_array, int iter);
t_room *clone_room(t_room *room, int room_counter, int next_room);


#endif
