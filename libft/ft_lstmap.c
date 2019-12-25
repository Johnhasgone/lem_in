/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cimogene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 18:45:43 by cimogene          #+#    #+#             */
/*   Updated: 2019/09/12 13:42:58 by cimogene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static t_list	*ft_delmaplist(t_list *lst)
{
	t_list		*del;

	while (lst)
	{
		del = lst;
		lst = lst->next;
		if (del->content)
			free(del->content);
		free(del);
	}
	return (NULL);
}

t_list			*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list		*new_lst;
	t_list		*start;

	if (!lst || !f)
		return (NULL);
	if (!(start = (t_list*)malloc(sizeof(t_list))))
		return (0);
	*start = *(f(lst));
	lst = lst->next;
	while (lst)
	{
		if (!(new_lst = (t_list*)malloc(sizeof(t_list))))
			return (ft_delmaplist(start));
		*new_lst = *(f(lst));
		ft_lstadd_end(&start, new_lst);
		lst = lst->next;
	}
	return (start);
}
