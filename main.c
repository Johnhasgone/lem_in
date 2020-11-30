/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cimogene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/26 17:10:28 by cimogene          #+#    #+#             */
/*   Updated: 2019/12/26 17:10:35 by cimogene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <printf.h>
#include "lem_in.h"

void switch_edges_to_duplicate(t_room **current_farm, int duplicate_room,
							   int original_room);

void print_farm_debug(t_room **farm)
{
	int i = 0;
	t_list * edges;
	printf("========================================================\n");
	while(farm[i])
	{
		printf("name: %s, index: %d, type: %d, dist: %d\n", farm[i]->name, i, farm[i]->type, farm[i]->dist);
		edges = farm[i]->out_edges;
		while(edges)
		{
			printf("    edge_out: from %s to %s, weight %d\n", farm[((t_edge*)(edges->content))->from]->name, farm[((t_edge*)(edges->content))->to]->name, ((t_edge*)(edges->content))->weight);
			edges = edges->next;
		}
		edges = farm[i]->in_edges;
		while(edges)
		{
			printf("    edge_in: from %s to %s, weight %d\n", farm[((t_edge*)(edges->content))->from]->name, farm[((t_edge*)(edges->content))->to]->name, ((t_edge*)(edges->content))->weight);
			edges = edges->next;
		}
		i++;
	}
}

void print_edges_debug(t_list *edges) {
	t_edge*	edge;
	int i = 1;

	printf("================================================================\n");
	while (edges)
	{
		edge = (t_edge*)edges->content;
		printf("%d. from: %d, to: %d, weight: %d\n", i, edge->from, edge->to, edge->weight);
		edges = edges->next;
		i++;
	}
}

int			check_integer(char *str)
{
	int		i;
	int		num;

	i = 0;
	while (str[i])
	{
		if (str[i] == '-' || str[i] == '+')
			i++;
		if (str[i] >= '0' && str[i] <= '9')
			i++;
		else
			return (0);
	}
	if ((num = ft_atoi(str)) < 0)
		num *= -1;
	if (num < 0 || (num == 0 && ft_strlen(str) > 2)
		|| (num == 1 && ft_strlen(str) > 2))
		return (0);
	while (num > 0)
	{
		if (num % 10 != str[--i] - '0')
			return (0);
		num /= 10;
	}
	return (1);
}

/*checking if the line contains enough information for creating an edge and creating it*/
int analyze_edge_line(char *line, t_room **farm, int room_counter)
{
	char	**edge_line;
	int		i;
	int 	j;
	t_edge	*edge_from;
	t_edge	*edge_to;

	i = 0;
	j = 0;
	edge_line = ft_strsplit(line, '-');
	while (i < room_counter)
	{
		if (ft_strcmp(edge_line[0], farm[i]->name) == 0)
			break ;
		i++;
	}
	while (j < room_counter)
	{
		if (ft_strcmp(edge_line[1], farm[j]->name) == 0)
			break ;
		j++;
	}
	if (i != room_counter && j != room_counter)
	{
		edge_from = create_edge(i, j, 1);
		edge_to = create_edge(j, i, 1);
		ft_lstadd_end(&(farm[i]->out_edges), ft_lstnew(edge_from, sizeof(*edge_from)));
		ft_lstadd_end(&(farm[j]->out_edges), ft_lstnew(edge_to, sizeof(*edge_to)));
		ft_lstadd_end(&(farm[i]->in_edges), ft_lstnew(edge_to, sizeof(*edge_to)));
		ft_lstadd_end(&(farm[j]->in_edges), ft_lstnew(edge_from, sizeof(*edge_from)));
		free(edge_from);
		free(edge_to);
		return (1);
	}
	return (0);
}

/* creating a new edge between rooms */
t_edge *create_edge(int from, int to, int weight) {
	t_edge *edge;

	edge = (t_edge*)malloc(sizeof(t_edge));
	edge->from = from;
	edge->to = to;
	edge->weight = weight;
	return edge;
}

/*
** checking a line on meeting the requirements
** correct room coordinates, out_edges, comments return 1
** all the other lines return 0
*/
int			analyze_line(char **line, int *ants, t_room **farm, int *room_counter)
{
	if (ft_countrows(*line, ' ') == 3)
		return (analyze_room_line(*line, farm, room_counter, SIMPLE));
	else if (ft_countrows(*line, '-') == 2)
		return (analyze_edge_line(*line, farm, *room_counter));
	else if (ft_strcmp(*line, "##start") == 0)
	{
		get_next_line(0, line);
		return (analyze_room_line(*line, farm, room_counter, START));
	}
	else if (ft_strcmp(*line, "##end") == 0)
	{
		get_next_line(0, line);
		return (analyze_room_line(*line, farm, room_counter, END));
	}
	else if (check_integer(*line) == 1)
	{
		*ants = ft_atoi(*line);
		if (*ants >= 0)
			return (1);
	}
	else if (*line[0] == '#')
		return (1);
	return (0);
}

int analyze_room_line(char *line, t_room **farm, int *room_counter, int type)
{
	t_room	*room;
	char 	**room_and_coord;

	if (ft_countrows(line, ' ') != 3)
		return (0);
	room_and_coord = ft_strsplit(line, ' ');
	if (check_integer(room_and_coord[1]) && check_integer(room_and_coord[2]))
	{
		room = (t_room*)malloc(sizeof(t_room));
		room->name = room_and_coord[0];
		room->coordinates[0] = ft_atoi(room_and_coord[1]);
		room->coordinates[1] = ft_atoi(room_and_coord[2]);
		room->type = type;
		room->out_edges = NULL;
		room->in_edges = NULL;
		if (type == START)
			room->dist = 0;
		else
			room->dist = INT32_MAX;
		farm[(*room_counter)++] = room;
		return (1);
	}
	return (0);
}

t_list *clone_edges(t_list *edges, int room_counter)
{
	t_list	*cloned_edges;
	t_list	*previous_edge;
	t_edge	*edge_content;

	previous_edge = NULL;
	cloned_edges = NULL;
	while (edges)
	{
		if (((t_edge*) edges->content)->weight >= 0)
		{
			if (!(edge_content = (t_edge *) malloc(sizeof(t_edge))))
				return NULL;
			edge_content->from = room_counter;
			edge_content->to = ((t_edge*) edges->content)->to;
			edge_content->weight = ((t_edge*) edges->content)->weight;
			if (!(cloned_edges = (t_list *) malloc(sizeof(t_list))))
				return NULL;
			cloned_edges->content = edge_content;
			cloned_edges->content_size = sizeof(edge_content);
			cloned_edges->next = previous_edge;
			previous_edge = cloned_edges;
		}
		edges = edges->next;
	}

	return (cloned_edges);
}

t_room *clone_room(t_room *room, int room_counter, int next_room)
{
	t_room	*clone_room;

	clone_room = (t_room*)malloc(sizeof(t_room));
	clone_room->name = ft_strjoin(room->name, "_duplicate");
	clone_room->coordinates[0] = room->coordinates[0];
	clone_room->coordinates[1] = room->coordinates[1];
	clone_room->type = DUPLICATE;
	clone_room->dist = room->dist;
	clone_room->out_edges = clone_edges(room->out_edges, room_counter);
	clone_room->in_edges = ft_lstnew(create_edge(next_room, room_counter, -1), sizeof(t_edge));
	return (clone_room);
}

t_edge	*edge_copy(t_edge *edge)
{
	t_edge *edge_copy;

	edge_copy = malloc(sizeof(t_edge));
	edge_copy->from = edge->from;
	edge_copy->to = edge->to;
	edge_copy->weight = edge->weight;
	return (edge_copy);
}

/*
 * edit edge to out in shortest path ()
 */
void
edit_edge_to_out(t_room **current_room, t_list *shortest_path, int in,
				 int out)
{
	t_list	*edges;
	int		from;
	t_list	*previous_edge;

	previous_edge = NULL;
	while (shortest_path)
	{
		if (((t_edge*)shortest_path->content)->from == in)
		{
			edges = current_room[((t_edge*)shortest_path->content)->to]->out_edges;
			while (edges)
			{
				if (((t_edge*)edges->content)->to == in)
				{
					((t_edge*)edges->content)->to = out;
					from = ((t_edge*)edges->content)->from;
					edges = current_room[in]->in_edges;
					while (edges)
					{
						if (((t_edge*)edges->content)->from == from
							&& ((t_edge*)edges->content)->to == in)
						{
							if (previous_edge == NULL)
							{
								previous_edge = edges;
								current_room[in]->in_edges = edges->next;
								free(previous_edge);
							}
							else
								delete_zero_edge(&previous_edge);
							break ;
						}
						previous_edge = edges;
						edges = edges->next;
					}
					return ;
				}
				edges = edges->next;
			}
		}
		shortest_path = shortest_path->next;
	}
}

void duplicate_rooms(t_room **current_farm, t_list *shortest_path, int *room_counter) {
	int room_number;

	while (shortest_path)
	{
		room_number = ((t_edge *) shortest_path->content)->from;

		//printf("duplicate_rooms\n");
		//print_farm_debug(current_farm);
		if (current_farm[room_number]->type == SIMPLE)
		{
			(*room_counter)++;
			current_farm[*room_counter] = clone_room(current_farm[room_number],
													 *room_counter, ((t_edge *) shortest_path->content)->to); // room_counter == out, room_number == in
			//printf("after duplicating room\n");
			//print_farm_debug(current_farm);
			edit_edge_to_out(current_farm, shortest_path, room_number, *room_counter);
			//printf("after edit_edge_to_out\n");
			//print_farm_debug(current_farm);
			remove_edges_from_in(&(current_farm[room_number]));
			//printf("after remove out_edges from in\n");
			//print_farm_debug(current_farm);
			add_zero_edge(current_farm, *room_counter, room_number, 0);
			//printf("after add zero edge\n");
			//print_farm_debug(current_farm);
			switch_edges_to_duplicate(current_farm, *room_counter, room_number);
			//printf("after switching edges to duplicate\n");
			//print_farm_debug(current_farm);
		}
		shortest_path = shortest_path->next;

	}
}

void switch_edges_to_duplicate(t_room **current_farm, int duplicate_room,
							   int original_room) {
	t_list	*duplicate_edges_out;
	t_list	*adjacent_edges_in;

	duplicate_edges_out = current_farm[duplicate_room]->out_edges;

	while (duplicate_edges_out)
	{
		if (((t_edge*)(duplicate_edges_out->content))->weight == 1)
		{
			adjacent_edges_in = current_farm[((t_edge*)(duplicate_edges_out->content))->to]->in_edges;
			while (adjacent_edges_in)
			{
				if (((t_edge*)(adjacent_edges_in->content))->from == original_room)
				{
					((t_edge*)(adjacent_edges_in->content))->from = duplicate_room;
					break ;
				}
				adjacent_edges_in = adjacent_edges_in->next;
			}
		}
		duplicate_edges_out = duplicate_edges_out->next;
	}
}

void remove_edges_from_in(t_room **room_in)
{
	t_list	*edges;
	t_list	*previous_edge;
	t_list	*result_edges;

	previous_edge = NULL;
	edges = (*room_in)->out_edges;
	result_edges = edges;

	while (edges)
	{
		if (((t_edge*)edges->content)->weight == 1)
		{
			if (previous_edge == NULL)
			{
				result_edges = edges->next;
				free(edges->content);
				free(edges);
				edges = result_edges;
			}
			else
			{
				previous_edge->next = edges->next;
				free(edges->content);
				free(edges);
				edges = previous_edge->next;
			}
		}
		else
		{
			previous_edge = edges;
			edges = edges->next;
		}
	}
	(*room_in)->out_edges = result_edges;
}

void add_zero_edge(t_room **farm, int from, int to, int weight)
{
	t_edge  *new_edge;
	t_list	*new_list;
	new_edge = (t_edge*)malloc(sizeof(t_edge));
	new_edge->from = from;                       // room_counter, from == out, room_number, to == in
	new_edge->to = to;
	new_edge->weight = weight;
	new_list = (t_list*)malloc(sizeof(t_list));
	new_list->content = new_edge;
	new_list->content_size = sizeof(new_edge);
	new_list->next = NULL;
	ft_lstadd(&farm[from]->out_edges, new_list);
	ft_lstadd(&farm[to]->in_edges, ft_lst_deep_copy(new_list, (void *(*)(
			void *)) edge_copy));
}

int read_instructions(t_room **farm, int *ants)
{
	char 		*line;
	int 		room_counter;

	room_counter = 0;
	while (get_next_line(0, &line))
	{
		if (ft_strcmp(line, "end") == 0)
			break;
		if (!analyze_line(&line, ants, farm, &room_counter)) {
			write(2, "Incorrect farm instructions\n", 28);
			exit(1);
		}
	}
	return (room_counter - 1);
}



t_list *find_shortest_paths(t_room **farm, int *room_counter, int ants,
							int *effectiveness)
{
	t_room	*current_farm[ROOM_NUM];
	t_list	*shortest_path_list;
	t_list	*shortest_path;
	int		max_path_count;
	int		i;
	int 	current_effectiveness;
	t_list *best_path_list;

	max_path_count = get_max_path_count(farm, *room_counter);
	shortest_path_list = NULL;
	initialize_current_farm(current_farm);
	i = 0;
	*effectiveness = INT32_MAX;
	best_path_list = NULL;
	while (i < max_path_count && i < ants)
	{
		ft_farm_copy(farm, current_farm);
		if (i != 0)
		{
			reverse_shortest_paths(current_farm, shortest_path_list);
			////printf("find_shortest_paths - after reverse_shortest_paths\n");
			////print_farm_debug(current_farm);
			duplicate_rooms(current_farm, shortest_path_list, room_counter);
			////printf("after duplicate room===============\n");
			//print_farm_debug(current_farm);
			bellman_ford_algo(current_farm, *room_counter);
			if (!check_for_connected_graph(current_farm, *room_counter))
				break ;
			shortest_path = get_shortest_path_before_collapse(current_farm,
															  *room_counter);
			//printf("shortest path before collapse\n");
			//print_edges_debug(shortest_path);
			shortest_path = collapse_shortest_path(current_farm, shortest_path);
			//printf("shortest path after collapse\n");
			//print_edges_debug(shortest_path);
			delete_bilateral_edges(shortest_path, &shortest_path_list);
			//printf("shortest path after delete bilateral edges\n");
			//print_edges_debug(shortest_path_list);
		}
		else
		{
			bellman_ford_algo(current_farm, *room_counter);
			if (!check_for_connected_graph(current_farm, *room_counter))
				return (NULL);													// Check for NULL in calling function (unconnected graph!!!)
			shortest_path = get_shortest_path_before_collapse(current_farm,
															  *room_counter);
			//printf("find_shortest_paths - after first get_shortest_path_before_collapse\n");
			//print_farm_debug(current_farm);
			shortest_path_list = ft_lst_deep_copy(shortest_path,
												  (void *(*)(void *)) edge_copy);
		}
		current_effectiveness = get_effectiveness_of_shortest_path_list(
				shortest_path_list, ants, i + 1, farm); // i + 1 - count of paths
		if (current_effectiveness <= *effectiveness)
		{
			*effectiveness = current_effectiveness;
			ft_free_lst(best_path_list);
			best_path_list = ft_lst_deep_copy(shortest_path_list,
											  (void *(*)(void *)) edge_copy);
		}
		else
			break ;
		i++;
	}
	free_current_farm(current_farm);
	return (best_path_list);
}

int
get_effectiveness_of_shortest_path_list(t_list *shortest_path_list, int ants,
										int iter, t_room **farm)
{
	int		*path_length_array;
	t_list	*shortest_path_list_copy;
	int		i;
	int		effectiveness;
	int		min;
	int		min_copy;

	i = 0;
	effectiveness = 0;
	shortest_path_list_copy = shortest_path_list;
	path_length_array = (int*)malloc(sizeof(int) * iter);
	while (shortest_path_list)
	{
		if (farm[((t_edge*)(shortest_path_list->content))->from]->type == START)
			path_length_array[i++] = get_path_length(shortest_path_list_copy,
													 ((t_edge *) (shortest_path_list->content))->to,
													 farm);
		shortest_path_list = shortest_path_list->next;
	}
	min = find_min_length(path_length_array, iter);
	min_copy = min - 1;
	while (ants > 0)
	{
		i = 0;
		while (i < iter)
		{
			if (path_length_array[i] == min)
			{
				path_length_array[i]++;
				ants--;
				if (ants == 0)
					break ;
			}
			i++;
		}
		effectiveness++;
		min++;
	}
	free(path_length_array);
	return effectiveness + min_copy;
}

int find_min_length(const int *path_length_array, int iter)
{
	int	min;
	int	i;

	min = path_length_array[0];
	i = 1;
	while (i < iter)
	{
		if (path_length_array[i] < min)
			min = path_length_array[i];
		i++;
	}
	return min;
}

/*
 * Calculate length of path starting with edge "START - to",
 * to is different for each disjoint path
 */
int get_path_length(t_list *shortest_path_list, int to, t_room **farm)
{
	int length;
	t_list	*shortest_path_list_copy;

	length = 1;
	shortest_path_list_copy = shortest_path_list;
	while (shortest_path_list)
	{
		if (((t_edge*)(shortest_path_list->content))->from == to)
		{
			length++;
			if (farm[((t_edge*)(shortest_path_list->content))->to]->type == END)
				break ;
			to = ((t_edge*)(shortest_path_list->content))->to;
			shortest_path_list = shortest_path_list_copy;
		}
		else
			shortest_path_list = shortest_path_list->next;
	}
	return (length);
}

void	delete_bilateral_edges(t_list *shortest_path, t_list **shortest_path_list)
{
	t_list	*shortest_path_list_copy;
	t_list	*initial_shortest_path_list;
	t_list	*previous_edge;
	int 	is_bilateral;

	initial_shortest_path_list = *shortest_path_list;
	while (shortest_path)
	{
		is_bilateral = 0;
		shortest_path_list_copy = initial_shortest_path_list;
		previous_edge = NULL;
		while (shortest_path_list_copy)
		{
			//printf("shortest_path=======");
			//print_edges_debug(shortest_path);
			//printf("shortest_path_list=======");
			//print_edges_debug(*shortest_path_list);
			if (((t_edge*)(shortest_path_list_copy->content))->to == ((t_edge*)(shortest_path->content))->from
					&& ((t_edge*)(shortest_path_list_copy->content))->from == ((t_edge*)(shortest_path->content))->to)
			{
				if (previous_edge == NULL)
				{
					previous_edge = *shortest_path_list;
					*shortest_path_list = (*shortest_path_list)->next;
					free(previous_edge);
				}
				else
					delete_zero_edge(&previous_edge);
				is_bilateral = 1;
				break ;
			}
			previous_edge = shortest_path_list_copy;
			shortest_path_list_copy = shortest_path_list_copy->next;
		}
		if (!is_bilateral)
			ft_lstadd(shortest_path_list, ft_lst_deep_copy(shortest_path,
													   (void *(*)(
															   void *)) edge_copy));
		shortest_path = shortest_path->next;
	}
}

t_list *collapse_shortest_path(t_room **farm, t_list *shortest_path)			// collapse duplicate vertices in shortest path
{
	t_edge* edge;
	t_edge* next_edge;

	t_list*	shortest_path_copy;

	shortest_path_copy = shortest_path;
	while (shortest_path)
	{
		edge = (t_edge *)shortest_path->content;
		if (shortest_path->next)
			next_edge = (t_edge *)(shortest_path->next->content);
		else
			next_edge = NULL;
		if (farm[edge->to]->type == DUPLICATE)
		{
			while (farm[edge->to]->out_edges)
			{
				if (((t_edge *)farm[edge->to]->out_edges->content)->weight == 0)
				{
					edge->to = ((t_edge *)farm[edge->to]->out_edges->content)->to;
					break ;
				}
				farm[edge->to]->out_edges = farm[edge->to]->out_edges->next;
			}
		}
		else if (farm[edge->from]->type == DUPLICATE)
		{
			while (farm[edge->from]->out_edges)
			{
				if (((t_edge *)farm[edge->from]->out_edges->content)->weight == 0)
				{
					edge->from = ((t_edge *)farm[edge->from]->out_edges->content)->to;
					break ;
				}
				farm[edge->from]->out_edges = farm[edge->from]->out_edges->next;
			}
		}
		if (next_edge != NULL && next_edge->weight == 0)
			delete_zero_edge(&shortest_path);
		shortest_path = shortest_path->next;
	}
	return shortest_path_copy;
}

void	delete_zero_edge(t_list **shortest_path)
{
	t_list*	zero_edge;

	if (shortest_path == NULL || *shortest_path == NULL)
		return ;
	zero_edge = (*shortest_path)->next;
	(*shortest_path)->next = (*shortest_path)->next->next;
	free(zero_edge);
}

int check_for_connected_graph(t_room **farm, int room_counter) {
	int		i;

	i = 0;
	while (i <= room_counter)
	{
		if (farm[i]->type == END)
		{
			if (farm[i]->dist == INT32_MAX)
				return (0);
			return (1);
		}
		i++;
	}
	return (0);
}

void bellman_ford_algo(t_room **farm, int room_counter)
{
	int i;
	int j;
	int to;
	t_list *edges;

	i = 0;
	//  ++i - starts with one because no sense comparing room to itself
	// (n - 1 comparisons should be done)
	while (++i <= room_counter)
	{
		j = 0;
		while (j <= room_counter)
		{
			if (farm[j]->dist != INT32_MAX)
			{
				edges = farm[j]->out_edges;
				while (edges)
				{
					to = ((t_edge *) (edges->content))->to;
				 	if (farm[to]->dist > farm[j]->dist + ((t_edge *) edges->content)->weight)
						farm[to]->dist = farm[j]->dist + ((t_edge *) edges->content)->weight;
					edges = edges->next;
				}
			}
			j++;
		}
	}
	//printf("after bellman_ford\n");
	//print_farm_debug(farm);
}



t_list	*get_shortest_path_before_collapse(t_room **farm, int room_counter)
{
	int		i;
	t_list*	shortest_path;

	i = 0;
	shortest_path = NULL;
	while (i <= room_counter)
	{
		if (farm[i]->type == END)
			break ;
		i++;
	}
	fill_shortest_path(farm, i, &shortest_path);
	//printf("====================inside get_shortest_path_before_collapse==========================\n");
	//print_edges_debug(shortest_path);
	return (shortest_path);
}

void fill_shortest_path(t_room **farm, int room_number, t_list **shortest_path)
{
	t_list* min_dist_room_edge;
	t_list *edges;
	int min_dist_room_number;
	t_list*	edge_to_path;
	int min_adjacent_distance;

	min_dist_room_edge = NULL;
	edges = farm[room_number]->in_edges;
	min_dist_room_number = room_number;
	min_adjacent_distance = INT32_MAX;
	while (edges)
	{
		if (farm[((t_edge*)edges->content)->from]->dist < min_adjacent_distance)
		{
			min_adjacent_distance = farm[((t_edge*)edges->content)->from]->dist;
			min_dist_room_number = ((t_edge*)edges->content)->from;
			min_dist_room_edge = edges;
		}
		edges = edges->next;
	}
	edge_to_path = ft_lst_deep_copy(min_dist_room_edge,
									(void *(*)(void *)) edge_copy);
	ft_lstadd(shortest_path, edge_to_path);
	if (farm[min_dist_room_number]->type != START)
		fill_shortest_path(farm, min_dist_room_number, shortest_path);
}

void reverse_shortest_paths(t_room **current_farm, t_list *shortest_path) // and destroy one of parallel out_edges
{
	int from;
	int to;

	while (shortest_path)
	{
		from = ((t_edge *) shortest_path->content)->from;
		to = ((t_edge *) shortest_path->content)->to;
		//printf("reverse_shortest_paths - before seek_and_negate\n");
		//print_farm_debug(current_farm);
		seek_and_negate_edge(&current_farm[to]->out_edges, from, to); // find edge with direction from TO to FROM and set weight to -1
		seek_and_negate_edge(&current_farm[from]->in_edges, from, to); // find edge with direction from TO to FROM and set weight to -1
		//printf("reverse_shortest_paths - after seek_and_negate\n");
		//print_farm_debug(current_farm);
		seek_and_destroy_edge(&current_farm[from]->out_edges, from, to); // find edge with direction from FROM to TO and DESTROY
		seek_and_destroy_edge(&current_farm[to]->in_edges, from, to); // find edge with direction from FROM to TO and DESTROY in in_edges
		//printf("reverse_shortest_paths - after seek_and_destroy\n");
		//print_farm_debug(current_farm);
		shortest_path = shortest_path->next;
	}
}

void seek_and_destroy_edge(t_list **edge_list, int from, int to) {
	t_list *current_edge;
	t_list *previous_edge;

	current_edge = *edge_list;
	previous_edge = NULL;
	while (current_edge)
	{
		if (((t_edge*) current_edge->content)->to == to &&
			((t_edge*) current_edge->content)->from == from)
		{
			if (previous_edge)
				previous_edge->next = current_edge->next;
			else
				*edge_list = current_edge->next;
			free(current_edge->content);
			free(current_edge);
			break ;
		}
		previous_edge = current_edge;
		current_edge = current_edge->next;
	}
}

void seek_and_negate_edge(t_list **edge_list, int from, int to) {
	t_list *current_edge;

	current_edge = *edge_list;
	while (current_edge)
	{
		if (((t_edge*) current_edge->content)->to == from &&
			((t_edge*) current_edge->content)->from == to)
		{
			((t_edge*) current_edge->content)->weight = -1;
			break ;
		}
		current_edge = current_edge->next;
	}
}

void initialize_current_farm(t_room **current_farm) {
	while (*current_farm)
	{
		*current_farm = (t_room*)malloc(sizeof(t_room));
		current_farm++;
	}
}

void free_current_farm(t_room **current_farm) {
	while (*current_farm)
	{
		free(*current_farm);
		current_farm++;
	}
}

void ft_farm_copy(t_room **farm, t_room **current_farm) {
	while (*farm)
	{
		*current_farm = (t_room*)malloc(sizeof(t_room));
		(*current_farm)->name = (*farm)->name;
		(*current_farm)->coordinates[0] = (*farm)->coordinates[0];
		(*current_farm)->coordinates[1] = (*farm)->coordinates[1];
		(*current_farm)->type = (*farm)->type;
		(*current_farm)->out_edges = (*farm)->out_edges;
		(*current_farm)->in_edges = (*farm)->in_edges;
		(*current_farm)->way = (*farm)->way;
		(*current_farm)->dist = (*farm)->dist;
		current_farm++;
		farm++;
	}
}


// max count of ways or max iteration number (min of out_edges from start and out_edges to end)
int get_max_path_count(t_room **farm, int room_counter) {
	int	max_path_count;
	int path_count;
	int	i;

	max_path_count = INT32_MAX;
	i = 0;
	while (i <= room_counter)
	{
		if (farm[i]->type == START && (path_count = ft_lst_length(farm[i]->out_edges)) < max_path_count)
			max_path_count = path_count;
		if (farm[i]->type == END && (path_count = ft_lst_length(farm[i]->in_edges)) < max_path_count)
			max_path_count = path_count;
		i++;
	}
	return (max_path_count);
}

int ft_lst_length(t_list *list) {
	int length;

	length = 0;
	while (list)
	{
		length++;
		list = list->next;
	}
	return (length);
}

void write_ant_moving(t_list *shortest_path_list, int ants, int effectiveness) {
	int	i;

	i = 0;
	while (i < effectiveness)
	{

		i++;
	}
}

int main()
{
	t_room		*farm[ROOM_NUM];
	t_list		*shortest_path_list;
	int			room_counter;
	int			ants;
	int			effectiveness;

	ants = -1;
	effectiveness = 0;
	room_counter = read_instructions(farm, &ants);

	//printf("main\n");
	print_farm_debug(farm);

	shortest_path_list = find_shortest_paths(farm, &room_counter, ants, &effectiveness);

	if (!shortest_path_list)
		write(2, "ERROR", 5);
	else
		write_ant_moving(shortest_path_list, ants, effectiveness);
	print_edges_debug(shortest_path_list);

//	for (int i = 0; i < 10000; i++)
//	{
//		if (farm[i])
//		{
//			put_room(&room_queue, farm[i]);
//		}
//	}
}

