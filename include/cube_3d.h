/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_3d.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbaudou <arbaudou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 16:50:30 by arbaudou          #+#    #+#             */
/*   Updated: 2025/09/12 17:25:40 by arbaudou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_3D_H
# define CUBE_3D_H

# include "mlx.h"
# include "parsing.h"
# include <math.h>
# include <stdio.h>

# define WIN_WIDTH 800
# define WIN_HEIGHT 600
# define ESC_KEY 65307 // 53 pour mac
# define MOVE_SPEED 0.1
# define ROT_SPEED 0.05
# define FOV 0.66
# define WALL_MARGIN 0.1
# define ROTATE_LEFT 65361
# define ROTATE_RIGHT 65363
# define MOVE_FORWARD 119
# define MOVE_BACKWARD 115
# define MOVE_LEFT 97
# define MOVE_RIGHT 100

// # define MOVE_FORWARD 122   // z
// # define MOVE_BACKWARD 115  // s
// # define MOVE_LEFT 113      // q
// # define MOVE_RIGHT 100     // d
// # define ROTATE_LEFT 65361  // flèche gauche
// # define ROTATE_RIGHT 65363 // flèche droite

// bpp = bits per pixel
// line_length = length of a line in bytes
// endian = endianness of the color format

typedef struct s_img
{
	void		*img;
	char		*addr;
	int			bpp;
	int			line_length;
	int			endian;
}				t_img;

typedef struct s_keys
{
	int			w;
	int			s;
	int			a;
	int			d;
	int			left;
	int			right;
}				t_keys;

typedef struct s_player
{
	float		x;
	float		y;
	float		dir_x;
	float		dir_y;
	float		plane_x;
	float		plane_y;
}				t_player;

typedef struct s_ray
{
	double		camera_x;
	double		ray_dir_x;
	double		ray_dir_y;
	int			map_x;
	int			map_y;
	double		delta_dist_x;
	double		delta_dist_y;
	int			step_x;
	int			step_y;
	double		side_dist_x;
	double		side_dist_y;
	int			side;
	double		perp_wall_dist;
	int			line_height;
	int			draw_start;
	int			draw_end;
	t_img		*tex;
	int			tex_x;
}				t_ray;

typedef struct s_game
{
	void		*mlx_ptr;
	void		*win_ptr;
	int			last_key;
	t_keys		keys;
	t_map		*map;
	t_img		img;
	t_player	player;
	t_img		tex_north;
	t_img		tex_south;
	t_img		tex_east;
	t_img		tex_west;
}				t_game;

/************** RAYCASTING **************/
int				start_engine(t_map *map);
void			init_player(t_player *player, t_map *map);
void			draw_background(t_img *img, int floor_color, int ceiling_color);
int				get_color_from_texture(t_map *map, int texture_index, float u,
					float v);
void			render_frame(t_game *game, t_map *map);
int				load_all_textures(t_game *game, t_map *map);
void			print_struct(t_map *map);
void			perform_dda(t_ray *ray, t_map *map);
void			calc_wall(t_ray *ray, t_game *game);
void			calc_tex_x(t_ray *ray, t_game *game);
void			draw_wall(t_ray *ray, t_game *game, int x);

/************** EVENT *************/
int				close_window(t_game *game);
int				key_press(int keycode, t_game *game);
int				key_release(int keycode, t_game *game);
void			move(t_game *game);
void			move_forward(t_player *player, t_map *map, double speed);
void			move_backward(t_player *player, t_map *map, double speed);
void			strafe_right(t_player *player, t_map *map, double speed);
void			strafe_left(t_player *player, t_map *map, double speed);
void			rotate_player(t_player *player, double angle);
int				is_free(double x, double y, t_map *map);

/************** INIT **************/

void			init_player(t_player *player, t_map *map);
void			init_keys(t_keys *keys);
void			init_ray(t_ray *ray, t_game *game, int x);

/************** UTILS **************/
void			free_struct(t_map *map);
void			my_mlx_pixel_put(t_img *img, int x, int y, int color);
void			cleanup_engine(t_game *game);
int				engine_check(t_game *game);
int				load_texture(t_game *game, char *path, t_img *tex);

#endif
