/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cimogene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 16:11:36 by cimogene          #+#    #+#             */
/*   Updated: 2019/09/11 19:54:50 by cimogene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*new_list;
	void	*cont_copy;

	new_list = (t_list*)malloc(sizeof(t_list));
	if (content == NULL)
		return (NULL);
	if (!(cont_copy = ft_memalloc(content_size)))
		return (NULL);
	if (new_list)
	{
		new_list->content = ft_memcpy(cont_copy, content, content_size);
		new_list->content_size = content_size;
		new_list->next = NULL;
		free((void*)content);
	}
	return (new_list);
}
