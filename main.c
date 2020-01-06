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

int			int_check(char *str)
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

int line_analyzer_edge(char *line, t_room **farm, int count)
{
	char	**edge;
	int		i;
	int 	j;

	i = 0;
	j = 0;
	edge = ft_strsplit(line, '-');
	while (i < count)
	{
		if (ft_strcmp(edge[0], farm[i]->name) == 0)
			break ;
		i++;
	}
	while (j < count)
	{
		if (ft_strcmp(edge[1], farm[j]->name) == 0)
			break ;
		j++;
	}
	if (i != count && j != count)
	{
		(farm[i]->edges)[(farm[i]->deg)++] = j;
		(farm[j]->edges)[(farm[j]->deg)++] = i;
		return (1);
	}
	return (0);
}

int			line_analyzer(char **line, int *ants, t_room **farm, int *i)
{
	if (ft_countrows(*line, ' ') == 3)
	{
		if (!line_analyzer_room(*line, farm, i, 0))
			return (0);
	}
	else if (ft_countrows(*line, '-') == 2)
	{
		if (!line_analyzer_edge(*line, farm, *i))
			return (0);
	}
	else if (ft_strcmp(*line, "##start") == 0)
	{
		get_next_line(0, line);
		if (!line_analyzer_room(*line, farm, i, 1))
			return (0);
	}
	else if (ft_strcmp(*line, "##end") == 0)
	{
		get_next_line(0, line);
		if (!line_analyzer_room(*line, farm, i, 2))
			return (0);
	}
	else if (int_check(*line) == 1)
		*ants = ft_atoi(*line);
	else if (*line[0] == '#')
		return (1);
	else
		return (0);
	return (1);
}

int line_analyzer_room(char *line, t_room **farm, int *i, int type)
{
	t_room	*room;
	char 	**room_and_coord;

	room_and_coord = ft_strsplit(line, ' ');
	if (int_check(room_and_coord[1]) && int_check(room_and_coord[2]))
	{
		room = (t_room*)malloc(sizeof(t_room));
		room->name = room_and_coord[0];
		room->coordinates[0] = ft_atoi(room_and_coord[1]);
		room->coordinates[1] = ft_atoi(room_and_coord[2]);
		room->deg = 0;
		room->type = type;
		farm[(*i)++] = room;
		return (1);
	}
	else
		return (0);
}

int main()
{
	char 		*line;
	t_room		*farm[10000];
	int			ants;
	int 		i;

	ants = -1;
	i = 0;
	while (get_next_line(0, &line))
	{
		if (!line_analyzer(&line, &ants, farm, &i))
			write(2, "Incorrect farm instructions\n", 28);
	}
}
