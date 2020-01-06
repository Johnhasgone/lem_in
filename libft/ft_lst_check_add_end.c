/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_check_add_end.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cimogene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 20:26:49 by cimogene          #+#    #+#             */
/*   Updated: 2019/12/12 18:16:00 by cimogene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_lst_check_add_end(t_list **alst, t_list *new)
{
	t_list	*elem;

	if (new == NULL)
		return (0);
	elem = *alst;
	if (elem == NULL)
		*alst = new;
	else
	{
		while (elem)
		{
			if (*(int*)elem->content == *(int*)new->content)
			{
				free(new->content);
				free(new);
				return (0);
			}
			if (!elem->next)
				break ;
			elem = elem->next;
		}
		elem->next = new;
	}
	return (1);
}
