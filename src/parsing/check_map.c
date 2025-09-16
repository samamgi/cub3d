/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbaudou <arbaudou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 14:36:48 by arbaudou          #+#    #+#             */
/*   Updated: 2025/09/11 16:43:57 by arbaudou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	flood_fill(t_map *map, int x, int y, char fill)
{
	if (x < 0 || y < 0 || x >= map->map_width || y >= map->map_height)
		return ;
	if (map->clean_map[y][x] != '0' && map->clean_map[y][x] != 'N'
		&& map->clean_map[y][x] != 'S' && map->clean_map[y][x] != 'E'
		&& map->clean_map[y][x] != 'W')
		return ;
	map->clean_map[y][x] = fill;
	flood_fill(map, x + 1, y, fill);
	flood_fill(map, x - 1, y, fill);
	flood_fill(map, x, y + 1, fill);
	flood_fill(map, x, y - 1, fill);
}

void	starting_orientation(t_map *map, char orientation)
{
	if (orientation == 'N')
		map->start_orientation = 0;
	else if (orientation == 'S')
		map->start_orientation = 1;
	else if (orientation == 'E')
		map->start_orientation = 2;
	else if (orientation == 'W')
		map->start_orientation = 3;
	else
		write(2, "Error: Invalid starting orientation\n", 36);
}

static int	find_player(t_map *map, int *x, int *y)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->map_height)
	{
		j = 0;
		while (j < map->map_width)
		{
			if (map->clean_map[i][j] == 'N' || map->clean_map[i][j] == 'S'
				|| map->clean_map[i][j] == 'E' || map->clean_map[i][j] == 'W')
			{
				starting_orientation(map, map->clean_map[i][j]);
				*x = j;
				*y = i;
				map->start_x = j;
				map->start_y = i;
				return (0);
			}
			j++;
		}
		i++;
	}
	return (-1);
}

static int	check_filled_edges(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->map_width)
	{
		if (map->clean_map[0][i] == 'F' || map->clean_map[map->map_height
			- 1][i] == 'F')
			return (-1);
		i++;
	}
	i = 0;
	while (i < map->map_height)
	{
		if (map->clean_map[i][0] == 'F' || map->clean_map[i][map->map_width
			- 1] == 'F')
			return (-1);
		i++;
	}
	return (0);
}

int	check_map(t_map *map)
{
	int	px;
	int	py;

	px = -1;
	py = -1;
	if (find_player(map, &px, &py) == -1)
	{
		write(2, "Error: Player not found in the map\n", 36);
		return (-1);
	}
	flood_fill(map, px, py, 'F');
	if (check_filled_edges(map) == -1)
	{
		write(2, "Error: Map is not closed\n", 26);
		return (-1);
	}
	replace_f_with_zero(map);
	if (check_colors(map) == -1)
		return (-1);
	if (check_valid_chars(map) == -1)
		return (-1);
	if (check_textures(map) == -1)
		return (-1);
	return (0);
}
