/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbaudou <arbaudou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 19:49:15 by arbaudou          #+#    #+#             */
/*   Updated: 2025/09/11 16:41:37 by arbaudou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_3d.h"

void	move_forward(t_player *player, t_map *map, double speed)
{
	double	next_x;
	double	next_y;

	next_x = player->x + player->dir_x * speed;
	next_y = player->y + player->dir_y * speed;
	if (is_free(next_x, player->y, map))
		player->x = next_x;
	if (is_free(player->x, next_y, map))
		player->y = next_y;
}

void	move_backward(t_player *player, t_map *map, double speed)
{
	double	next_x;
	double	next_y;

	next_x = player->x - player->dir_x * speed;
	next_y = player->y - player->dir_y * speed;
	if (is_free(next_x, player->y, map))
		player->x = next_x;
	if (is_free(player->x, next_y, map))
		player->y = next_y;
}

void	strafe_right(t_player *player, t_map *map, double speed)
{
	double	next_x;
	double	next_y;
	double	perp_x;
	double	perp_y;

	perp_x = -player->dir_y;
	perp_y = player->dir_x;
	next_x = player->x + perp_x * speed;
	next_y = player->y + perp_y * speed;
	if (is_free(next_x, player->y, map))
		player->x = next_x;
	if (is_free(player->x, next_y, map))
		player->y = next_y;
}

void	strafe_left(t_player *player, t_map *map, double speed)
{
	double	next_x;
	double	next_y;
	double	perp_x;
	double	perp_y;

	perp_x = player->dir_y;
	perp_y = -player->dir_x;
	next_x = player->x + perp_x * speed;
	next_y = player->y + perp_y * speed;
	if (is_free(next_x, player->y, map))
		player->x = next_x;
	if (is_free(player->x, next_y, map))
		player->y = next_y;
}

void	rotate_player(t_player *player, double angle)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = player->dir_x;
	old_plane_x = player->plane_x;
	player->dir_x = player->dir_x * cos(angle) - player->dir_y * sin(angle);
	player->dir_y = old_dir_x * sin(angle) + player->dir_y * cos(angle);
	player->plane_x = player->plane_x * cos(angle) - player->plane_y
		* sin(angle);
	player->plane_y = old_plane_x * sin(angle) + player->plane_y * cos(angle);
}
