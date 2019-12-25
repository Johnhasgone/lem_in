/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_lst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cimogene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 15:19:24 by cimogene          #+#    #+#             */
/*   Updated: 2019/09/12 15:27:16 by cimogene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list		*ft_free_lst(t_list *lst)
{
	t_list	*del;

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
