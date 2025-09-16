/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbaudou <arbaudou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 16:50:38 by arbaudou          #+#    #+#             */
/*   Updated: 2025/09/11 16:54:20 by arbaudou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <string.h>
# include "libft.h"

// For start orientation : 0: North, 1: South, 2: East, 3: West

typedef struct s_map
{
	char	*path_north;
	char	*path_south;
	char	*path_east;
	char	*path_west;
	char	**map_data;
	char	**clean_map;
	char	start_orientation;
	int		start_x;
	int		start_y;
	int		floor_color;
	int		ceiling_color;
	int		map_width;
	int		map_height;
}				t_map;

/************** PARSING **************/
char	**create_tab(const char *input);
int		check_extension(const char *filename);
int		parse(const char *input, t_map *map);
int		parse_input(const char *input, t_map *map);
int		parse_params(char **tab, t_map *map);
int		parse_map(char **file_lines, int start_index, t_map *map);
int		check_map(t_map *map);
int		check_textures(t_map *map);
int		check_colors(t_map *map);
int		check_valid_chars(t_map *map);

/*********** INIT **************/
void	init_map(t_map *map);

/************** UTILS **************/
int		ft_max(int a, int b);
void	ft_free_tab(char **tab);
void	replace_f_with_zero(t_map *map);
void	trim_newline_end(char *line);

#endif