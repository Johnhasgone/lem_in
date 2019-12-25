/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cimogene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 11:47:52 by cimogene          #+#    #+#             */
/*   Updated: 2019/09/10 14:07:36 by cimogene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	count_of_spaces(char const *s)
{
	int		count;
	int		end;

	count = 0;
	while (s[count] == ' ' || s[count] == '\t' || s[count] == '\n')
		count++;
	if (s[count] == '\0')
		return (count);
	end = ft_strlen(s) - 1;
	while (s[end] == ' ' || s[end] == '\t' || s[end] == '\n')
	{
		end--;
		count++;
	}
	return (count);
}

char		*ft_strtrim(char const *s)
{
	int		i;
	int		j;
	int		len;
	char	*new_str;

	if (s == NULL)
		return (NULL);
	i = 0;
	j = 0;
	len = ft_strlen(s) - count_of_spaces(s);
	if ((new_str = (char*)malloc(sizeof(char) * (len + 1))))
	{
		while (s[j] == ' ' || s[j] == '\n' || s[j] == '\t')
			j++;
		while (i < len)
		{
			new_str[i] = s[j];
			i++;
			j++;
		}
		new_str[i] = '\0';
		return (new_str);
	}
	else
		return (NULL);
}
