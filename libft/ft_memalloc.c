/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cimogene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 22:11:16 by cimogene          #+#    #+#             */
/*   Updated: 2019/09/07 23:37:20 by cimogene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void		*ft_memalloc(size_t size)
{
	void	*mem;
	size_t	i;

	i = 0;
	mem = malloc(size);
	if (mem)
	{
		return (ft_memset(mem, 0, size));
	}
	else
		return (NULL);
}
