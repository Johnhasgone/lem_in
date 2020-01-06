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

#include "libft/libft.h"

typedef struct		s_room
{
	char			*name;
	int 			coordinates[2];
	int				edges[10000];
	int				deg;
	int 			type;	// 0 - ordinary, 1 - start, 2 - finish
	int 			way;
}					t_room;

int line_analyzer_room(char *line, t_room **farm, int *i, int type);
int		line_analyzer_edge(char *line, t_room **farm, int count);

#endif
