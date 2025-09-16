/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbaudou <arbaudou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 10:47:12 by arbaudou          #+#    #+#             */
/*   Updated: 2025/09/04 10:49:00 by arbaudou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_3d.h"

int	is_free(double x, double y, t_map *map)
{
	int	map_x;
	int	map_y;

	map_x = (int)x;
	map_y = (int)y;
	if (map_x < 0 || map_x >= map->map_width || map_y < 0
		|| map_y >= map->map_height)
		return (0);
	if (map->clean_map[map_y][map_x] == '1')
		return (0);
	if (map->clean_map[map_y][(int)(x + WALL_MARGIN)] == '1')
		return (0);
	if (map->clean_map[map_y][(int)(x - WALL_MARGIN)] == '1')
		return (0);
	if (map->clean_map[(int)(y + WALL_MARGIN)][map_x] == '1')
		return (0);
	if (map->clean_map[(int)(y - WALL_MARGIN)][map_x] == '1')
		return (0);
	return (1);
}

void	move(t_game *game)
{
	if (game->keys.w)
		move_forward(&game->player, game->map, MOVE_SPEED);
	if (game->keys.s)
		move_backward(&game->player, game->map, MOVE_SPEED);
	if (game->keys.a)
		strafe_left(&game->player, game->map, MOVE_SPEED);
	if (game->keys.d)
		strafe_right(&game->player, game->map, MOVE_SPEED);
	if (game->keys.left)
		rotate_player(&game->player, -ROT_SPEED);
	if (game->keys.right)
		rotate_player(&game->player, ROT_SPEED);
}
