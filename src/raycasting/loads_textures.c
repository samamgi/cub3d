/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loads_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbaudou <arbaudou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 23:46:04 by arbaudou          #+#    #+#             */
/*   Updated: 2025/09/12 15:29:03 by arbaudou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_3d.h"

int	load_all_textures(t_game *game, t_map *map)
{
	if (load_texture(game, map->path_north, &game->tex_north) == -1)
		return (-1);
	if (load_texture(game, map->path_south, &game->tex_south) == -1)
		return (-1);
	if (load_texture(game, map->path_east, &game->tex_east) == -1)
		return (-1);
	if (load_texture(game, map->path_west, &game->tex_west) == -1)
		return (-1);
	return (0);
}

void	ray_side(t_ray *ray, t_game *game)
{
	if (ray->side == 0)
	{
		if (ray->step_x > 0)
			ray->tex = &game->tex_west;
		else
			ray->tex = &game->tex_east;
	}
	else
	{
		if (ray->step_y > 0)
			ray->tex = &game->tex_north;
		else
			ray->tex = &game->tex_south;
	}
}

void	calc_wall(t_ray *ray, t_game *game)
{
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->map_x - game->player.x + (1 - ray->step_x)
				/ 2) / ray->ray_dir_x;
	else
		ray->perp_wall_dist = (ray->map_y - game->player.y + (1 - ray->step_y)
				/ 2) / ray->ray_dir_y;
	ray->line_height = (int)(WIN_HEIGHT / ray->perp_wall_dist);
	ray->draw_start = -ray->line_height / 2 + WIN_HEIGHT / 2;
	ray->draw_end = ray->line_height / 2 + WIN_HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	if (ray->draw_end >= WIN_HEIGHT)
		ray->draw_end = WIN_HEIGHT - 1;
	ray_side(ray, game);
}

void	calc_tex_x(t_ray *ray, t_game *game)
{
	double	wall_x;

	if (ray->side == 0)
		wall_x = game->player.y + ray->perp_wall_dist * ray->ray_dir_y;
	else
		wall_x = game->player.x + ray->perp_wall_dist * ray->ray_dir_x;
	wall_x -= floor(wall_x);
	ray->tex_x = (int)(wall_x * ray->tex->line_length / (ray->tex->bpp / 8));
	if ((ray->side == 0 && ray->step_x > 0) || (ray->side == 1
			&& ray->step_y < 0))
		ray->tex_x = ray->tex->line_length / (ray->tex->bpp / 8) - ray->tex_x
			- 1;
}

void	draw_wall(t_ray *ray, t_game *game, int x)
{
	int	y;
	int	d;
	int	tex_y;
	int	color;
	int	tex_height;

	if (!ray->tex || !ray->tex->addr)
		return ;
	calc_tex_x(ray, game);
	tex_height = ray->tex->line_length / (ray->tex->bpp / 8);
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		d = y * 256 - WIN_HEIGHT * 128 + ray->line_height * 128;
		tex_y = ((d * tex_height) / ray->line_height) / 256;
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= tex_height)
			tex_y = tex_height - 1;
		color = *(unsigned int *)(ray->tex->addr + (tex_y
					* ray->tex->line_length + ray->tex_x * (ray->tex->bpp
						/ 8)));
		my_mlx_pixel_put(&game->img, x, y, color);
		y++;
	}
}
