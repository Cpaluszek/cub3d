/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 14:51:59 by cpalusze          #+#    #+#             */
/*   Updated: 2023/03/08 13:30:03 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "cub3d.h"
# include "mlx_utils.h"
# include "vectors.h"
# include "colors.h"

typedef struct s_ray {
	t_int_vector 	map_pos;
	t_int_vector 	moving_direction;
	t_float_vector	next_wall_hit;
	t_float_vector	closest_side_wall;
	t_float_vector	direction;
	float 			relative_hit_on_wall;
}	t_ray;

typedef struct s_player {
	t_float_vector	pos;
	t_float_vector	dir;
	t_float_vector	move;
	float			rotate;
	float			angle;
	int 			attack_state;
}	t_player;

typedef struct s_texture_path {
	char	*north_texture_path;
	char	*south_texture_path;
	char	*west_texture_path;
	char	*east_texture_path;
	char	*door_texture_path;
}	t_texture_path;

typedef struct s_texture {
	void *address;
	char *text;
	int bits_per_pixel;
	int line_length;
	int endian;
	int width;
	int height;
} t_texture;

typedef struct s_mlx_data {
	void		*mlx;
	void		*mlx_win;
	t_img_data	mlx_img;
}	t_mlx_data;

// Todo: create texture strect
typedef struct s_display {
	t_color			floor_color;
	t_color			ceiling_color;
	int				**north_texture;
	int				**south_texture;
	int				**west_texture;
	int				**east_texture;
	int				**door_texture;
	t_int_vector	north_texture_size;
	t_int_vector	south_texture_size;
	t_int_vector	east_texture_size;
	t_int_vector	west_texture_size;
	t_int_vector 	maze_size;
	int				ray_size[WIN_W];
	int 			wall_pos_x[WIN_W];
	char			ray_texture[WIN_W];
	char			**grid_maze;
	//
	int 			**torch_idle_texture;
	int 			**torch_attack_texture;
	t_int_vector	torch_idle_texture_size;
	t_int_vector	torch_attack_texture_size;
}	t_display;

typedef struct s_cub3d
{
	// Note: remove map_path from struct
	char			*map_path;
	// Note: remove from struct ??
	char			**map_information;
	t_texture_path	textures_paths;
	t_mlx_data		mlx_data;
	t_display		display;
	t_player		player;
}	t_cub3d;

enum e_result
{
	SUCCESS = 0,
	ERROR = 1,
};

#endif
