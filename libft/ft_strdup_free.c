/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nslughor <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 14:29:21 by nslughor          #+#    #+#             */
/*   Updated: 2019/10/23 13:01:55 by cimogene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup_free(const char *src)
{
	int		i;
	char	*src2;

	i = 0;
	if (!(src2 = (char*)malloc(sizeof(char) * (ft_strlen(src) + 1))))
		return (NULL);
	while (src[i])
	{
		src2[i] = src[i];
		i++;
	}
	src2[i] = '\0';
	free((char*)src);
	return (src2);
}
