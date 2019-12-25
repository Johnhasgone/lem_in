/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpop_end.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cimogene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 21:43:18 by cimogene          #+#    #+#             */
/*   Updated: 2019/12/01 21:43:23 by cimogene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstpop_end(t_list **begin_list)
{
	t_list	*elem;
	t_list	*ret;

	elem = *begin_list;
	if (elem == NULL)
		return (NULL);
	if (elem->next == NULL)
	{
		*begin_list = NULL;
		return (elem);
	}
	while (elem->next->next)
		elem = elem->next;
	ret = elem->next;
	elem->next = NULL;
	return (ret);
}
