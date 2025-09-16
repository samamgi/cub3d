/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_params.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbaudou <arbaudou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 20:21:55 by arbaudou          #+#    #+#             */
/*   Updated: 2025/09/04 10:44:19 by arbaudou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	parse_color(char *line)
{
	int		r;
	int		g;
	int		b;
	char	**split;

	line += 1;
	while (*line == ' ')
		line++;
	split = ft_split(line, ',');
	if (!split || ft_tablen(split) != 3)
		return (-1);
	r = atoi(split[0]);
	g = atoi(split[1]);
	b = atoi(split[2]);
	ft_free_tab(split);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (-1);
	return ((r << 16) | (g << 8) | b);
}

static char	*dup_path(const char *line)
{
	while (*line && *line != ' ')
		line++;
	while (*line == ' ')
		line++;
	return (ft_strdup(line));
}

static int	assign_param(char *line, t_map *map)
{
	if (strncmp(line, "NO ", 3) == 0 && !map->path_north)
		map->path_north = dup_path(line);
	else if (strncmp(line, "SO ", 3) == 0 && !map->path_south)
		map->path_south = dup_path(line);
	else if (strncmp(line, "EA ", 3) == 0 && !map->path_east)
		map->path_east = dup_path(line);
	else if (strncmp(line, "WE ", 3) == 0 && !map->path_west)
		map->path_west = dup_path(line);
	else if (strncmp(line, "F ", 2) == 0 && map->floor_color == 0)
		map->floor_color = parse_color(line);
	else if (strncmp(line, "C ", 2) == 0 && map->ceiling_color == 0)
		map->ceiling_color = parse_color(line);
	else
		return (0);
	return (1);
}

int	parse_params(char **tab, t_map *map)
{
	int	i;
	int	found;

	i = 0;
	found = 0;
	while (tab[i])
	{
		if (assign_param(tab[i], map))
			found++;
		else if (tab[i][0] == '1' || tab[i][0] == ' ')
			break ;
		i++;
	}
	if (found != 6)
	{
		write(2, "Error: Missing parameters in map file\n", 38);
		return (-1);
	}
	return (i);
}
