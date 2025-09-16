/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbaudou <arbaudou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 21:25:16 by arbaudou          #+#    #+#             */
/*   Updated: 2025/09/04 10:27:39 by arbaudou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	get_map_size(char **lines, int start_index, int *width, int *height)
{
	int	i;
	int	line_len;

	*width = 0;
	*height = 0;
	i = start_index;
	while (lines[i])
	{
		line_len = 0;
		while (lines[i][line_len])
			line_len++;
		if (line_len > 0 && lines[i][line_len - 1] == '\n')
			line_len--;
		*width = ft_max(*width, line_len);
		(*height)++;
		i++;
	}
}

static char	*copy_clean_line(char *src, int width)
{
	char	*clean_line;
	int		len;
	int		i;

	len = 0;
	while (src[len] && src[len] != '\n')
		len++;
	clean_line = malloc(sizeof(char) * (width + 1));
	if (!clean_line)
		return (NULL);
	i = 0;
	while (i < len)
	{
		clean_line[i] = src[i];
		i++;
	}
	while (i < width)
	{
		clean_line[i] = ' ';
		i++;
	}
	clean_line[width] = '\0';
	return (clean_line);
}

int	parse_map(char **file_lines, int start_index, t_map *map)
{
	int	i;

	get_map_size(file_lines, start_index, &map->map_width, &map->map_height);
	map->clean_map = malloc(sizeof(char *) * (map->map_height + 1));
	if (!map->clean_map)
	{
		write(2, "Error: Memory allocation failed for map data\n", 45);
		return (-1);
	}
	i = 0;
	while (i < map->map_height)
	{
		map->clean_map[i] = NULL;
		map->clean_map[i] = copy_clean_line(file_lines[start_index + i],
				map->map_width);
		if (!map->clean_map[i])
		{
			ft_free_tab(map->clean_map);
			return (write(2, "Error: Malloc failed for map line\n", 35), -1);
		}
		i++;
	}
	map->clean_map[i] = NULL;
	return (0);
}
