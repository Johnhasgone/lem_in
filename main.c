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
	t_list	*room;
	char 	**room_and_coord;

	vertex = ft_countrows(line, ' ');
	edge = ft_countrows(line, '-');
	if (vertex == 3)
	{
		room_and_coord = ft_strsplit(line, ' ');
		room = ft_lstnew(room_and_coord[0], ft_strlen(room_and_coord[0]) + 1);
		(*farm)->content = ft_lstnew(&room, 8);
		return (1);
	}
	if (edge == 2)
	{

	}
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
