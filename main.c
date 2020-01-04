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


int line_analyzer(char *line, int* ants, t_list **farm)
{
	int 	vertex;
	int		edge;
	t_room	*room;
	char 	**room_and_coord;
	char 	**edges;

	vertex = ft_countrows(line, ' ');
	edge = ft_countrows(line, '-');
	if (vertex == 3)
	{
		room = (t_room*)malloc(20); // как определить размер памяти для
		// аллокации
		room_and_coord = ft_strsplit(line, ' ');
		room->name = room_and_coord[0];
		(*farm)->content = ft_lstnew(room, 48);
		return (1);
	}
	else
		return (0);
}

int main()
{
	char 	*line;
	t_list	*farm;
	int		ants;
	

	ants = -1;
	farm = NULL;

	while (get_next_line(0, &line))
	{
		if (line_analyzer(line, &ants, &farm))
			farm_maker(line, &farm);
		else
			error_report
	}
}
