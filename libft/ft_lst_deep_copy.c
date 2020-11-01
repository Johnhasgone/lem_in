/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_deep_copy.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cimogene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 18:00:14 by cimogene          #+#    #+#             */
/*   Updated: 2019/09/11 18:16:29 by cimogene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"


t_list *ft_node_copy(t_list *list, void* (*ft_struct_copy)(void *))
{
	t_list *list_copy;

	list_copy = (t_list*)malloc(sizeof(t_list));
	list_copy->content = ft_struct_copy(list->content);
	list_copy->content_size = list->content_size;
	list_copy->next = NULL;
	return (list_copy);
}

t_list		*ft_lst_deep_copy(t_list *list, void* (*ft_struct_copy)(void *))
{
	t_list	*list_copy;
	t_list	*list_copy_start;
	t_list	*list_copy_prev;

	list_copy_start = NULL;
	if (list)
	{
		list_copy = ft_node_copy(list, ft_struct_copy);
		list = list->next;
		list_copy_prev = list_copy;
		list_copy_start = list_copy;
	}
	while (list)
	{
		list_copy = ft_node_copy(list, ft_struct_copy);
		list = list->next;
		list_copy_prev->next = list_copy;
		list_copy_prev = list_copy;
	}
	return (list_copy_start);
}

