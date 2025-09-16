/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbaudou <arbaudou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 17:54:16 by arbaudou          #+#    #+#             */
/*   Updated: 2025/09/12 17:26:46 by arbaudou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_3d.h"

int	close_window(t_game *game)
{
	if (game->img.img)
		mlx_destroy_image(game->mlx_ptr, game->img.img);
	if (game->win_ptr)
		mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	if (game->mlx_ptr)
	{
		mlx_destroy_display(game->mlx_ptr);
		free(game->mlx_ptr);
	}
	free_struct(game->map);
	free(game->map);
	exit(0);
	return (0);
}

// printf("Key pressed: %d\n", keycode);
int	key_press(int keycode, t_game *game)
{
	if (keycode == MOVE_FORWARD)
		game->keys.w = 1;
	else if (keycode == MOVE_BACKWARD)
		game->keys.s = 1;
	else if (keycode == MOVE_LEFT)
		game->keys.a = 1;
	else if (keycode == MOVE_RIGHT)
		game->keys.d = 1;
	else if (keycode == ROTATE_LEFT)
		game->keys.left = 1;
	else if (keycode == ROTATE_RIGHT)
		game->keys.right = 1;
	else if (keycode == ESC_KEY)
	{
		close_window(game);
		free_struct(game->map);
		free(game->map);
	}
	return (0);
}

// printf("Key released: %d\n", keycode);
int	key_release(int keycode, t_game *game)
{
	if (keycode == MOVE_FORWARD)
		game->keys.w = 0;
	else if (keycode == MOVE_BACKWARD)
		game->keys.s = 0;
	else if (keycode == MOVE_LEFT)
		game->keys.a = 0;
	else if (keycode == MOVE_RIGHT)
		game->keys.d = 0;
	else if (keycode == ROTATE_LEFT)
		game->keys.left = 0;
	else if (keycode == ROTATE_RIGHT)
		game->keys.right = 0;
	return (0);
}
