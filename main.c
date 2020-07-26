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
	clone_room->type = room->type;
}

void duplicate_rooms(t_room **farm)
{

}

int main()
{
	char 		*line;
	t_room		*farm[10000];
	int			ants;
	int 		room_counter;
	t_queue 	*room_queue;

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
	for (int i = 0; i < 10000; i++)
	{
		if (farm[i])
		{
			put_room(&room_queue, farm[i]);
		}
	}
}
