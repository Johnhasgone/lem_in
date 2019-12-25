/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cimogene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 22:19:31 by cimogene          #+#    #+#             */
/*   Updated: 2019/09/09 22:44:57 by cimogene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>

char		*ft_strsub(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*sub_s;

	if (s == NULL)
		return (NULL);
	i = 0;
	if ((sub_s = (char*)malloc(sizeof(char) * (len + 1))))
	{
		while (i < len)
		{
			sub_s[i] = s[start + i];
			i++;
		}
		sub_s[i] = '\0';
		return (sub_s);
	}
	else
		return (NULL);
}
