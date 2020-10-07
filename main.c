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

#include <stdbool.h>
#include "lem_in.h"



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
		edge_from = create_edge(i, j);
		set_weight(&edge_from, 1);
		edge_to = create_edge(j, i);
		set_weight(&edge_to, 1);
		ft_lstadd_end(&(farm[i]->edges), ft_lstnew(edge_from, sizeof(*edge_from)));
		ft_lstadd_end(&(farm[j]->edges), ft_lstnew(edge_to, sizeof(*edge_to)));
		return (1);
	}
	return (0);
}

/* setting weight of an edge */
void		set_weight(t_edge **edge, int weight) {
	(*edge)->weight = weight;
}

/* creating a new edge between rooms */
t_edge		*create_edge(int from, int to) {
	t_edge *edge;

	edge = (t_edge*)malloc(sizeof(t_edge));
	edge->from = from;
	edge->to = to;
	return edge;
}

/*
** checking a line on meeting the requirements
** correct room coordinates, edges, comments return 1
** all the other lines return 0
*/
int			analyze_line(char **line, int *ants, t_room **farm, int *room_counter)
{
	if (ft_countrows(*line, ' ') == 3)
		return (analyze_room_line(*line, farm, room_counter, 0));
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

	room_and_coord = ft_strsplit(line, ' ');
	if (check_integer(room_and_coord[1]) && check_integer(room_and_coord[2]))
	{
		room = (t_room*)malloc(sizeof(t_room));
		room->name = room_and_coord[0];
		room->coordinates[0] = ft_atoi(room_and_coord[1]);
		room->coordinates[1] = ft_atoi(room_and_coord[2]);
		room->deg = 0;
		room->type = type;
		room->edges = NULL;
		if (type == START)
			room->dist = 0;
		else
			room->dist = INT32_MAX;
		farm[(*room_counter)++] = room;
		return (1);
	}
	return (0);
}

t_room *clone_room(t_room *room)
{
	t_room	*clone_room;

	clone_room = (t_room*)malloc(sizeof(t_room));
	clone_room->name = room->name;
	clone_room->coordinates[0] = room->coordinates[0];
	clone_room->coordinates[1] = room->coordinates[1];
	clone_room->deg = room->deg;
	clone_room->type = DUPLICATE;
	clone_room->dist = room->dist;
	clone_room->edges = ft_lst_deep_copy(room->edges, edge_copy);
	return clone_room;
}

t_edge	*edge_copy(t_edge *edge)
{
	t_edge *edge_copy;

	edge_copy = malloc(sizeof(t_edge));
	edge_copy->from = edge->from;
	edge_copy->to = edge->to;
	edge_copy->weight = edge->weight;
	return edge_copy;
}

void duplicate_rooms(t_room **current_farm, t_list *shortest_path, int *room_counter) {
	int room_number;
	t_edge *new_edge;
	while (shortest_path)
	{
		room_number = ((t_edge *) shortest_path->content)->from;
		if (current_farm[room_number]->type == SIMPLE)
		{
			current_farm[*room_counter] = clone_room(current_farm[room_number]); // room_counter == out, room_number == in
			remove_edges_to_out(current_farm, *room_counter);
			remove_edges_from_in(&(current_farm[room_number]));
			add_zero_edge(current_farm, *room_counter, room_number, 0);
			(*room_counter)++;
		}
		shortest_path = shortest_path->next;

	}
}

void remove_edges_from_in(t_room **room_in)
{
	t_list **edges;
	t_list *next_edge;

	*edges = (*room_in)->edges;

	while (*edges)
	{
		next_edge = (*edges)->next;
		free((*edges)->content);
		free((*edges));
		*edges = next_edge;
	}
}

void remove_edges_to_out(t_room **current_farm, int out) {
	t_list	*edges;

	int		neighbor_index;

	edges = current_farm[out]->edges;
	while (edges)
	{
		neighbor_index = ((t_edge*) edges->content)->to;
		seek_and_destroy_edge(&current_farm[neighbor_index]->edges, neighbor_index, out);
		edges = edges->next;
	}
}

void add_zero_edge(t_room **farm, int from, int to, int weight)
{
	t_edge *new_edge;
	new_edge = (t_edge*)malloc(sizeof(t_edge));
	new_edge->from = from;                       // room_counter, from == out, room_number, to == in
	new_edge->to = to;
	new_edge->weight = weight;
	ft_lstadd(&farm[from]->edges, (t_list*) new_edge);
}

int read_instructions(t_room **farm, int *ants)
{
	char 		*line;
	int 		room_counter;

	room_counter = 0;
	while (get_next_line(0, &line))
	{
		if (ft_strcmp(line, "end_input") == 0)
			break;
		if (!analyze_line(&line, ants, farm, &room_counter)) {
			write(2, "Incorrect farm instructions\n", 28);
			exit(1);
		}
	}
	return room_counter;
}

int main()
{
	t_room		*farm[ROOM_NUM];
	t_queue 	*room_queue;
	t_list		*shortest_path_list;
	int			room_counter;
	int			ants;

	ants = -1;
	room_counter = read_instructions(farm, &ants);

	shortest_path_list = find_shortest_paths(farm, &room_counter, ants);

	write_ant_moving(shortest_path_list);

	for (int i = 0; i < 10000; i++)
	{
		if (farm[i])
		{
			put_room(&room_queue, farm[i]);
		}
	}


}

t_list *find_shortest_paths(t_room **farm, int *room_counter, int ants)
{
	t_room	*current_farm[ROOM_NUM];
	t_edge	**overlap_path_list;
	t_list	*shortest_path_list;
	t_list	*shortest_path;
	int		max_path_count;
	int		i;
	int 	effectiveness;
	int 	current_effectiveness;
	t_list *best_path_list;

	max_path_count = get_max_path_count(*farm);
	shortest_path_list = NULL;
	initialize_current_farm(current_farm);
	i = 0;
	effectiveness = INT32_MAX;
	best_path_list = NULL;
	while (i < max_path_count)
	{
		ft_farm_copy(farm, current_farm);
		if (i != 0)
		{
			reverse_shortest_paths(current_farm, shortest_path_list);
			duplicate_rooms(current_farm, shortest_path_list, room_counter);
			bellman_ford_algo(current_farm, *room_counter);
			if (!check_for_connected_graph(current_farm, *room_counter))
				break;
			shortest_path = get_shortest_path_before_collapse(current_farm,
															  *room_counter);
			shortest_path = collapse_shortest_path(farm, shortest_path);
			delete_bilateral_edges(shortest_path, &shortest_path_list);
		}
		else
		{
			bellman_ford_algo(current_farm, *room_counter);
			if (!check_for_connected_graph(current_farm, *room_counter))
				return (NULL);													// Check for NULL in calling function (unconnected graph!!!)
		}
		current_effectiveness = get_effectiveness_of_shortest_path_list(
				shortest_path_list, ants, i + 1, NULL); // i + 1 - count of paths
		if (current_effectiveness <= effectiveness)
		{
			effectiveness = current_effectiveness;
			best_path_list = ft_lst_deep_copy(shortest_path_list);
		}
		else
			break ;
		i++;
	}
	free_current_farm(current_farm);
	//ft_free_lst(shortest_path_list);
	return best_path_list;
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
	int		j;

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
	while (ants > 0)
	{
		while (j < iter)
		{
			if (path_length_array[j] == min)
			{
				path_length_array[j]++;
				ants--;
				if (ants == 0)
					break ;
			}
			j++;
		}
		effectiveness++;
		min++;
	}
	free(path_length_array);
	return effectiveness;
}

int find_min_length(int *path_length_array, int iter)
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

int get_path_length(t_list *shortest_path_list, int to, t_room **farm)
{
	int length;
	t_list	*shortest_path_list_copy;

	length = 0;
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
	t_list	*previous_edge;

	shortest_path_list_copy = *shortest_path_list;
	previous_edge = NULL;
	while (shortest_path)
	{
		while (shortest_path_list_copy)
		{
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
				break ;
			}
			ft_lstadd(shortest_path_list, shortest_path);
			previous_edge = shortest_path_list_copy;
			shortest_path_list_copy = shortest_path_list_copy->next;
		}
		shortest_path = shortest_path->next;
	}
}

t_list *collapse_shortest_path(t_room **farm, t_list *shortest_path)			// collapse duplicate vertices in shortest path
{
	t_edge* edge;
	t_edge* next_edge;

	while (shortest_path)
	{
		edge = (t_edge *)shortest_path->content;
		next_edge = (t_edge *)(shortest_path->next->content);
		if (farm[edge->to]->type == DUPLICATE)
		{
			while (farm[edge->to]->edges)
			{
				if (((t_edge *)farm[edge->to]->edges->content)->weight == 0)
				{
					edge->to = ((t_edge *)farm[edge->to]->edges->content)->to;
					break;
				}
				farm[edge->to]->edges = farm[edge->to]->edges->next;
			}
		}
		if (next_edge != NULL && next_edge->weight == 0)
			delete_zero_edge(&shortest_path);
		shortest_path = shortest_path->next;
	}
	return shortest_path;
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
	while (i < room_counter)
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
	while (++i < room_counter)
	{
		j = 0;
		while (j < room_counter)
		{
			if (farm[j]->dist != INT32_MAX)
			{
				edges = farm[j]->edges;
				while (edges)
				{
					to = ((t_edge *) edges)->to;
					if (farm[to]->dist > farm[j]->dist + ((t_edge *) edges->content)->weight)
						farm[to]->dist = farm[j]->dist + ((t_edge *) edges->content)->weight;
					edges = edges->next;
				}
			}
			j++;
		}
	}
}

t_list	*get_shortest_path_before_collapse(t_room **farm, int room_counter)
{
	int		i;
	t_list*	shortest_path;

	i = 0;
	shortest_path = NULL;
	while (i < room_counter)
	{
		if (farm[i]->type == END)
			break;
		i++;
	}
	fill_shortest_path(farm, i, &shortest_path);
	return (shortest_path);
}

void fill_shortest_path(t_room **farm, int room_number,
						t_list **shortest_path)
{
	int min_dist;
	t_list* min_dist_room_edge;
	t_list *edges;
	int min_dist_room_number;

	min_dist = INT32_MAX;
	min_dist_room_edge = NULL;
	edges = farm[room_number]->edges;
	while (edges)
	{
		if (farm[((t_edge*)edges->content)->to]->dist < min_dist)
		{
			min_dist = farm[((t_edge*)edges->content)->to]->dist;
			min_dist_room_edge = edges;
			min_dist_room_number = ((t_edge*)edges->content)->to;
		}
		edges = edges->next;
	}
	ft_lstadd(shortest_path, min_dist_room_edge);
	if (farm[min_dist_room_number]->type != START)
		fill_shortest_path(farm, min_dist_room_number, shortest_path);
}

void reverse_shortest_paths(t_room **current_farm, t_list *shortest_path) // and destroy one of parallel edges
{
	int from;
	int to;

	while (shortest_path)
	{
		from = ((t_edge *) shortest_path->content)->from;
		to = ((t_edge *) shortest_path->content)->to;
		seek_and_negate_edge(&current_farm[to]->edges, from, to); // find edge with direction from TO to FROM and set weight to -1
		seek_and_destroy_edge(&current_farm[from]->edges, from, to); // find edge with direction from FROM to TO and DESTROY
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
			break;
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
			break;
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
		(*current_farm)->name = (*farm)->name;
		(*current_farm)->coordinates[0] = (*farm)->coordinates[0];
		(*current_farm)->coordinates[1] = (*farm)->coordinates[1];
		(*current_farm)->deg = (*farm)->deg;
		(*current_farm)->type = (*farm)->type;
		(*current_farm)->edges = (*farm)->edges;
		(*current_farm)->way = (*farm)->way;
		current_farm++;
		farm++;
	}
}


// max count of ways or max iteration number (min of edges from start and edges to end)
int get_max_path_count(t_room *farm) {
	int	max_path_count;
	int path_count;

	max_path_count = INT32_MAX;
	while (farm)
	{
		if (farm->type != 0)
		{
			path_count = ft_lst_length(farm->edges);
			if (max_path_count == INT32_MAX)
				max_path_count = path_count;
			else
			{
				if (path_count < max_path_count)
					return path_count;
				return max_path_count;
			}
		}
	}
}

int ft_lst_length(t_list *list) {
	int length;

	length = 0;
	while (list)
	{
		length++;
		list = list->next;
	}
	return length;
}

void write_ant_moving(t_list *shortest_path_list) {

}


