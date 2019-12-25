/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cimogene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 23:17:18 by cimogene          #+#    #+#             */
/*   Updated: 2019/09/14 20:28:44 by cimogene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int				ft_atoi(const char *str)
{
	long long	res;
	int			isneg;
	int			i;

	res = 0;
	isneg = 0;
	i = 0;
	while (str[i] == '\0' || str[i] == '\n' || str[i] == '\t' ||
	str[i] == '\v' || str[i] == '\f' || str[i] == '\r' || str[i] == ' ')
		i++;
	if (str[i] == '-')
		isneg = -1;
	if ((str[i] == '-') || (str[i] == '+'))
		i++;
	while ((str[i] >= '0') && (str[i] <= '9'))
	{
		res = res * 10 + (str[i++] - '0');
		if (res < 0 && isneg == -1)
			return (0);
		if (res < 0 && isneg != -1)
			return (-1);
	}
	if (isneg == -1)
		return (-(int)res);
	return ((int)res);
}
