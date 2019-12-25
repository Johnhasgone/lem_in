/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cimogene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 19:15:15 by cimogene          #+#    #+#             */
/*   Updated: 2019/09/09 17:54:00 by cimogene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void					*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*dst_cast;
	unsigned const char	*src_cast;
	size_t				i;

	dst_cast = dst;
	src_cast = src;
	i = 0;
	if (src_cast < dst_cast)
	{
		while (len > 0)
		{
			dst_cast[len - 1] = src_cast[len - 1];
			len--;
		}
	}
	else if (src_cast > dst_cast)
	{
		while (i < len)
		{
			dst_cast[i] = src_cast[i];
			i++;
		}
	}
	return (dst);
}
