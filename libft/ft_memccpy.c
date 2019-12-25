/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cimogene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 10:41:39 by cimogene          #+#    #+#             */
/*   Updated: 2019/09/09 12:21:26 by cimogene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void				*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t			i;
	unsigned char	*dst_cast;
	unsigned char	*src_cast;

	c = (unsigned char)c;
	i = 0;
	dst_cast = (unsigned char*)dst;
	src_cast = (unsigned char*)src;
	while (i < n)
	{
		dst_cast[i] = src_cast[i];
		if (dst_cast[i] == c)
			return (&dst_cast[i + 1]);
		i++;
	}
	return (NULL);
}
