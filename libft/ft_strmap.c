/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cimogene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 14:33:25 by cimogene          #+#    #+#             */
/*   Updated: 2019/09/09 18:00:39 by cimogene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char		*ft_strmap(char const *s, char (*f)(char))
{
	char	*fresh_str;
	int		i;

	i = 0;
	if (s == NULL)
		return (NULL);
	fresh_str = (char*)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (fresh_str)
	{
		while (s[i] != 0)
		{
			fresh_str[i] = f(s[i]);
			i++;
		}
		fresh_str[i] = '\0';
		return (fresh_str);
	}
	else
		return (NULL);
}
