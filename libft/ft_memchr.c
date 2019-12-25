/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cimogene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 11:58:52 by cimogene          #+#    #+#             */
/*   Updated: 2019/09/09 16:22:26 by cimogene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void				*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*s_cast;

	i = 0;
	s_cast = (unsigned char*)s;
	c = (unsigned char)c;
	while (i < n)
	{
		if (s_cast[i] == c)
			return (&s_cast[i]);
		i++;
	}
	return (NULL);
}
