/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cimogene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 22:51:06 by cimogene          #+#    #+#             */
/*   Updated: 2019/09/11 12:21:15 by cimogene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char		*ft_strjoin(char const *s1, char const *s2)
{
	char	*new_str;
	size_t	i;
	size_t	j;
	size_t	size1;
	size_t	size2;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	i = 0;
	j = 0;
	size1 = ft_strlen_p(s1);
	size2 = ft_strlen_p(s2);
	new_str = (char*)malloc(sizeof(char) * (size1 + size2 + 1));
	if (new_str)
	{
		while (j < size1)
			new_str[i++] = s1[j++];
		j = 0;
		while (j < size2)
			new_str[i++] = s2[j++];
		new_str[i] = '\0';
		return (new_str);
	}
	else
		return (NULL);
}
