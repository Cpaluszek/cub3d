/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 14:51:59 by cpalusze          #+#    #+#             */
/*   Updated: 2023/03/08 14:49:13 by cpalusze         ###   ########.fr       */
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

typedef struct s_mlx_data {
	void		*mlx;
	void		*mlx_win;
	t_img_data	mlx_img;
}	t_mlx_data;

typedef struct s_texture {
	t_int_vector	size;
	int				**content;
}	t_texture;

typedef struct s_display {
	t_int_vector 	maze_size;
	char			**grid_maze;
	char			ray_texture[WIN_W];
	int				ray_size[WIN_W];
	int 			wall_pos_x[WIN_W];
	t_color			floor_color;
	t_color			ceiling_color;
	t_texture 		north_tex;
	t_texture 		south_tex;
	t_texture 		west_tex;
	t_texture 		east_tex;
	t_texture 		door_tex;
	t_texture 		torch_idle_tex;
	t_texture 		torch_attack_tex;
}	t_display;

typedef struct s_cub3d
{
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
