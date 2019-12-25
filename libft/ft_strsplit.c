/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cimogene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 15:10:07 by cimogene          #+#    #+#             */
/*   Updated: 2019/09/12 13:26:40 by cimogene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int		ft_countrows(char const *s, char c)
{
	int			i;
	int			rows;

	i = 0;
	rows = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		if (s[i] != c && s[i] != '\0')
			rows++;
		while (s[i] != c && s[i] != '\0')
			i++;
	}
	return (rows);
}

static char		**ft_delmap(char **str, int i)
{
	while (i >= 0)
	{
		free(str[i]);
		str[i] = NULL;
		i--;
	}
	free(str);
	str = NULL;
	return (str);
}

static char		**ft_emptymap(char const *s, char c)
{
	int			i;
	int			j;
	int			rows;
	int			columns;
	char		**map;

	i = 0;
	j = 0;
	rows = ft_countrows(s, c);
	if (!(map = (char**)malloc(sizeof(char*) * (rows + 1))))
		return (NULL);
	while (s[i] != '\0' && j < rows)
	{
		columns = 0;
		while (s[i] == c && s[i] != '\0')
			i++;
		while (s[i] != c && s[i++] != '\0')
			columns++;
		if (!(map[j++] = (char*)malloc(sizeof(char) * (columns + 1))))
			return (ft_delmap(map, j - 2));
	}
	map[j] = NULL;
	return (map);
}

char			**ft_strsplit(char const *s, char c)
{
	char		**map;
	int			i;
	int			j;
	int			k;
	int			rows;

	if (s == NULL)
		return (NULL);
	i = 0;
	k = 0;
	rows = ft_countrows(s, c);
	if (!(map = ft_emptymap(s, c)))
		return (NULL);
	while (s[k] != '\0' && i < rows)
	{
		j = 0;
		while (s[k] == c && s[k] != '\0')
			k++;
		while (s[k] != c && s[k] != '\0')
			map[i][j++] = s[k++];
		map[i++][j] = '\0';
	}
	return (map);
}
