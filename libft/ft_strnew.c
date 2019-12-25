/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cimogene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 16:38:25 by cimogene          #+#    #+#             */
/*   Updated: 2019/09/12 12:52:55 by cimogene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strnew(size_t size)
{
	char	*dst;
	size_t	i;

	if (size > size + 1)
		return (NULL);
	i = 0;
	dst = (char *)malloc(size + 1);
	if (dst)
	{
		while (i <= size + 1)
		{
			dst[i] = '\0';
			i++;
		}
		return (dst);
	}
	else
		return (NULL);
}
