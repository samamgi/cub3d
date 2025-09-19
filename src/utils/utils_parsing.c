/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbaudou <arbaudou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 21:26:27 by arbaudou          #+#    #+#             */
/*   Updated: 2025/09/17 17:08:29 by arbaudou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	ft_max(int a, int b)
{
	if (a > b)
		return (a);
	else
		return (b);
}

void	replace_f_with_zero(t_map *map)
{
	int	y;
	int	x;

	y = 0;
	while (y < map->map_height)
	{
		x = 0;
		while (x < map->map_width)
		{
			if (map->clean_map[y][x] == 'F')
				map->clean_map[y][x] = '0';
			x++;
		}
		y++;
	}
}

void	trim_newline_end(char *line)
{
	int	len;

	if (!line)
		return ;
	len = ft_strlen(line);
	if (len == 0)
		return ;
	if (line[len - 1] == '\n')
		line[len - 1] = '\0';
}

int	check_border(t_map *map, int row)
{
	int	i;
	int	j;

	i = ft_strlen(map->clean_map[row - 1]);
	j = ft_strlen(map->clean_map[row]);
	if (i > j && row != 0)
	{
		while (map->clean_map[row - 1][j] != '\0')
		{
			if (map->clean_map[row - 1][j] == 'F')
				return (-1);
			j++;
		}
	}
	return (0);
}
