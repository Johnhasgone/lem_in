/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cimogene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 20:39:24 by cimogene          #+#    #+#             */
/*   Updated: 2019/09/11 12:23:23 by cimogene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	int_size(int n)
{
	int		res;
	int		size;

	res = n;
	size = 0;
	while (res != 0)
	{
		res = res / 10;
		size++;
	}
	return (size);
}

char		*ft_itoa(int n)
{
	char	*str;
	int		size;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n <= 0)
		size = int_size(n) + 1;
	else
		size = int_size(n);
	str = (char*)malloc(sizeof(char) * (size + 1));
	if (!str)
		return (NULL);
	if (n < 0)
	{
		str[0] = '-';
		n = -n;
	}
	str[size] = '\0';
	str[--size] = n % 10 + 48;
	while (n /= 10)
		str[--size] = n % 10 + 48;
	return (str);
}
