/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbaudou <arbaudou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 19:12:04 by arbaudou          #+#    #+#             */
/*   Updated: 2025/09/12 17:23:07 by arbaudou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	parse(const char *input, t_map *map)
{
	int	map_start;

	if (parse_input(input, map) == -1)
		return (-1);
	map_start = parse_params(map->map_data, map);
	if (map_start == -1)
		return (-1);
	if (parse_map(map->map_data, map_start, map) == -1)
		return (-1);
	if (check_map(map) == -1)
		return (-1);
	return (0);
}
