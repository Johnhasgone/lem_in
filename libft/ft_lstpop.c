/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pop_lst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hluthor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 14:32:44 by cimogene          #+#    #+#             */
/*   Updated: 2019/09/12 15:32:34 by cimogene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list	*ft_lstpop(t_list **begin_list)
{
	t_list	*new_elem;

	if (*begin_list == NULL)
		return (NULL);
	new_elem = *begin_list;
	*begin_list = (*begin_list)->next;
	new_elem->next = NULL;
	return (new_elem);
}
