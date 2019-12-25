/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cimogene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 18:31:00 by cimogene          #+#    #+#             */
/*   Updated: 2019/09/09 18:44:06 by cimogene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*fresh_str;
	int		i;

	i = 0;
	if (s == NULL)
		return (NULL);
	if ((fresh_str = (char*)malloc(sizeof(char) * (ft_strlen(s) + 1))))
	{
		while (s[i] != '\0')
		{
			fresh_str[i] = f(i, s[i]);
			i++;
		}
		fresh_str[i] = '\0';
		return (fresh_str);
	}
	else
		return (NULL);
}
