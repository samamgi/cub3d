/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbaudou <arbaudou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 15:27:30 by arbaudou          #+#    #+#             */
/*   Updated: 2025/09/11 16:45:07 by arbaudou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static char	*normalize_line(char *line, int width)
{
	int		i;
	char	*new_line;

	new_line = malloc(sizeof(char) * (width + 1));
	if (!new_line)
		return (NULL);
	i = 0;
	while (line[i] && i < width)
	{
		new_line[i] = line[i];
		i++;
	}
	while (i < width)
	{
		new_line[i] = ' ';
		i++;
	}
	new_line[i] = '\0';
	return (new_line);
}

int	normalize_map(t_map *map, char **lines, int start_index)
{
	int	i;

	map->clean_map = malloc(sizeof(char *) * (map->map_height + 1));
	if (!map->clean_map)
		return (-1);
	i = 0;
	while (i < map->map_height)
	{
		map->clean_map[i] = normalize_line(lines[start_index + i],
				map->map_width);
		if (!map->clean_map[i])
			return (-1);
		i++;
	}
	map->clean_map[i] = NULL;
	return (0);
}
