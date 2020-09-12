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

#include "lem_in.h"

int get_max_path_count(t_room *farm);

int ft_lst_length(t_list *list);

void ft_farm_copy(t_room **farm, t_room **current_farm);

void initialize_current_farm(t_room **current_farm);


void reverse_shortest_paths(t_room **current_farm, t_list *shortest_path);

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
		return (analyze_room_line(*line, farm, room_counter, 1));
	}
	else if (ft_strcmp(*line, "##end") == 0)
	{
		get_next_line(0, line);
		return (analyze_room_line(*line, farm, room_counter, 2));
	}
	else if (check_integer(*line) == 1)
	{
		*ants = ft_atoi(*line);
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
			current_farm[*room_counter] = clone_room(current_farm[room_number]);
			add_new_edge(current_farm, *room_counter, room_number, 0);
			(*room_counter)++;
		}
		shortest_path = shortest_path->next;

	}
}

void add_new_edge(t_room **farm, int from, int to, int weight)
{
	t_edge *new_edge;
	new_edge = (t_edge*)malloc(sizeof(t_edge));
	new_edge->from = from;
	new_edge->to = to;
	new_edge->weight = weight;
	ft_lstadd(&farm[from]->edges, (t_list*) new_edge);
}

int read_instructions(t_room **farm)
{
	char 		*line;
	int			ants;
	int 		room_counter;

	ants = -1;
	room_counter = 0;
	while (get_next_line(0, &line))
	{
		if (ft_strcmp(line, "end_input") == 0)
			break;
		if (!analyze_line(&line, &ants, farm, &room_counter)) {
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

	room_counter = read_instructions(farm);

	shortest_path_list = find_shortest_paths(farm, &room_counter);

	write_ant_moving(shortest_path_list);

	for (int i = 0; i < 10000; i++)
	{
		if (farm[i])
		{
			put_room(&room_queue, farm[i]);
		}
	}


}

t_list *find_shortest_paths(t_room **farm, int *room_counter)
{
	t_room	*current_farm[ROOM_NUM];
	t_edge	**overlap_path_list;
	t_list	*shortest_path_list;
	int		max_path_count;
	int		i;

	max_path_count = get_max_path_count(*farm);
	initialize_current_farm(current_farm);
	i = 0;
	while (i < max_path_count)
	{
		ft_farm_copy(farm, current_farm);

		if (i != 0)
		{
			reverse_shortest_paths(current_farm, shortest_path_list);
			duplicate_rooms(current_farm, shortest_path_list, room_counter);
		}
		i++;
	}
	free_current_farm(current_farm);
	return shortest_path_list;
}

void reverse_shortest_paths(t_room **current_farm, t_list *shortest_path) // and destroy one of parallel edges
{
	int from;
	int to;

	while (shortest_path)
	{
		from = ((t_edge *) shortest_path->content)->from;
		to = ((t_edge *) shortest_path->content)->to;
		seek_and_minusize(current_farm[to]->edges, from, to); // find edge with direction from TO to FROM and set weight to -1
		seek_and_destroy(current_farm[from]->edges, from, to); // find edge with direction from FROM to TO and DESTROY
		shortest_path = shortest_path->next;
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


