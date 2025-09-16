/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbaudou <arbaudou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 21:01:43 by arbaudou          #+#    #+#             */
/*   Updated: 2025/09/04 13:46:53 by arbaudou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_3d.h"

// void	print_struct(t_map *map)
// {
// 	if (!map)
// 	{
// 		ft_printf("Map is NULL\n");
// 		return ;
// 	}
// 	ft_printf("North Path: %s\n", map->path_north ? map->path_north : "None");
// 	ft_printf("South Path: %s\n", map->path_south ? map->path_south : "None");
// 	ft_printf("East Path: %s\n", map->path_east ? map->path_east : "None");
// 	ft_printf("West Path: %s\n", map->path_west ? map->path_west : "None");
// 	ft_printf("Start Orientation: %d\n", map->start_orientation);
// 	ft_printf("Floor Color: %d\n", map->floor_color);
// 	ft_printf("Ceiling Color: %d\n", map->ceiling_color);
// 	ft_printf("Map Width: %d\n", map->map_width);
// 	ft_printf("Map Height: %d\n", map->map_height);
// 	ft_printf("Start Position: (%d, %d)\n", map->start_x, map->start_y);
// 	if (map->clean_map)
// 	{
// 		ft_printf("Clean Map Data:\n");
// 		print_split(map->clean_map);
// 	}
// 	else
// 	{
// 		ft_printf("Map Data: None\n");
// 	}
// }
