/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbaudou <arbaudou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 21:10:01 by arbaudou          #+#    #+#             */
/*   Updated: 2025/09/11 16:57:25 by arbaudou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_3d.h"

void	draw_background(t_img *img, int floor_color, int ceiling_color)
{
	int	x;
	int	y;

	y = 0;
	while (y < WIN_HEIGHT / 2)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			my_mlx_pixel_put(img, x, y, ceiling_color);
			x++;
		}
		y++;
	}
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			my_mlx_pixel_put(img, x, y, floor_color);
			x++;
		}
		y++;
	}
}

void	perform_dda(t_ray *ray, t_map *map)
{
	int	hit;

	hit = 0;
	while (!hit)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (map->clean_map[ray->map_y][ray->map_x] == '1')
			hit = 1;
	}
}

void	render_frame(t_game *game, t_map *map)
{
	int		x;
	t_ray	ray;

	draw_background(&game->img, map->floor_color, map->ceiling_color);
	x = 0;
	while (x < WIN_WIDTH)
	{
		init_ray(&ray, game, x);
		perform_dda(&ray, map);
		calc_wall(&ray, game);
		draw_wall(&ray, game, x);
		x++;
	}
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->img.img, 0, 0);
}

int	game_loop(t_game *game)
{
	draw_background(&game->img, game->map->floor_color,
		game->map->ceiling_color);
	move(game);
	render_frame(game, game->map);
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->img.img, 0, 0);
	return (0);
}

int	start_engine(t_map *map)
{
	t_game	game;

	game.map = map;
	game.mlx_ptr = mlx_init();
	if (engine_check(&game) == -1)
		return (cleanup_engine(&game), -1);
	init_player(&game.player, map);
	init_keys(&game.keys);
	mlx_hook(game.win_ptr, 2, 1L << 0, key_press, &game);
	mlx_hook(game.win_ptr, 3, 1L << 1, key_release, &game);
	mlx_hook(game.win_ptr, 17, 0, close_window, &game);
	load_all_textures(&game, map);
	mlx_loop_hook(game.mlx_ptr, game_loop, &game);
	mlx_loop(game.mlx_ptr);
	return (0);
}
