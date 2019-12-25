/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cimogene <cimogene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 18:12:48 by cimogene          #+#    #+#             */
/*   Updated: 2019/09/24 13:45:52 by cimogene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "libft.h"

static void			add_lst(t_lst **begin_list, char *s, int fd)
{
	t_lst			*current;
	t_lst			*new_lst;
	char			*tmp;

	current = *begin_list;
	while (current)
	{
		if (current->fdesc == fd)
		{
			tmp = current->str;
			current->str = ft_strjoin(current->str, s);
			free(tmp);
			tmp = NULL;
			break ;
		}
		current = current->next;
	}
	if (current == NULL)
	{
		new_lst = (t_lst *)malloc(sizeof(t_lst));
		new_lst->fdesc = fd;
		new_lst->str = ft_strdup(s);
		new_lst->next = *begin_list;
		*begin_list = new_lst;
	}
}

static void			del_lst(t_lst **begin_list, int fd)
{
	t_lst			*new_elem;
	t_lst			*save_elem;

	new_elem = *begin_list;
	if (new_elem->fdesc == fd)
	{
		*begin_list = new_elem->next;
		free(new_elem);
		new_elem = NULL;
	}
	else
	{
		while (new_elem->next)
		{
			if ((new_elem->next)->fdesc == fd)
			{
				save_elem = new_elem->next;
				free(new_elem->next);
				new_elem->next = save_elem->next;
				free(save_elem);
				save_elem = NULL;
			}
			new_elem = new_elem->next;
		}
	}
}

static t_lst		*find_lst(t_lst *begin_lst, int fd)
{
	t_lst			*current;

	current = begin_lst;
	while (current)
	{
		if (current->fdesc == fd)
			return (current);
		current = current->next;
	}
	return (NULL);
}

static int			read_line(int fd, t_lst *begin_lst, char **line)
{
	t_lst			*current;
	int				i;
	char			*tmp;

	i = 0;
	current = find_lst(begin_lst, fd);
	if (current && current->str)
	{
		if (ft_strchr(current->str, '\n'))
		{
			while ((current->str)[i] != '\n')
				i++;
			tmp = current->str;
			(current->str)[i] = '\0';
			*line = ft_strdup(current->str);
			if ((current->str)[i + 1])
				current->str = ft_strdup(&(current->str)[i + 1]);
			else
				current->str = NULL;
			free(tmp);
			tmp = NULL;
			return (1);
		}
	}
	return (0);
}

int					get_next_line(const int fd, char **line)
{
	int				read_res;
	char			buffer[BUFF_SIZE + 1];
	static t_lst	*save_lst;
	t_lst			*current;

	while (fd >= 0 && line)
	{
		if (read_line(fd, save_lst, line))
			return (1);
		if ((read_res = read(fd, buffer, BUFF_SIZE)) == -1)
			return (-1);
		else if (read_res == 0)
		{
			if ((current = find_lst(save_lst, fd)) && current->str)
			{
				*line = ft_strdup(current->str);
				del_lst(&save_lst, fd);
				return (1);
			}
			return (0);
		}
		buffer[read_res] = '\0';
		add_lst(&save_lst, buffer, fd);
	}
	return (-1);
}
