/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_raycasting.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbaudou <arbaudou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 21:28:54 by arbaudou          #+#    #+#             */
/*   Updated: 2025/09/11 16:49:02 by arbaudou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_3d.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
		return ;
	dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

int	engine_check(t_game *game)
{
	if (!game->mlx_ptr)
		return (write(2, "Error: Failed to initialize MLX\n", 33), -1);
	game->win_ptr = mlx_new_window(game->mlx_ptr, WIN_WIDTH, WIN_HEIGHT,
			"Cube_3D");
	if (!game->win_ptr)
		return (cleanup_engine(game), write(2,
				"Error: Failed to create window\n", 32), -1);
	game->img.img = mlx_new_image(game->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	if (!game->img.img)
		return (write(2, "Error: Failed to create image\n", 31), -1);
	game->img.addr = mlx_get_data_addr(game->img.img, &game->img.bpp,
			&game->img.line_length, &game->img.endian);
	return (0);
}

int	load_texture(t_game *game, char *path, t_img *tex)
{
	tex->img = mlx_xpm_file_to_image(game->mlx_ptr, path, &tex->bpp,
			&tex->line_length);
	if (!tex->img)
		return (-1);
	tex->addr = mlx_get_data_addr(tex->img, &tex->bpp, &tex->line_length,
			&tex->endian);
	return (0);
}
