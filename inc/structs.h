/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlitaudo <jlitaudo@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 14:51:59 by cpalusze          #+#    #+#             */
/*   Updated: 2023/03/06 10:18:23 by jlitaudo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "cub3d.h"
# include "mlx_utils.h"

// Todo: create a vector header
// Todo: double or float ?
typedef struct s_float_vector {
	float	x;
	float	y;
}	t_float_vector;

typedef struct s_int_vector {
	int x;
	int	y;
}	t_int_vector;

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
}	t_player;

typedef struct s_rgb
{
	unsigned char	blu;
	unsigned char	gre;
	unsigned char	red;
}	t_rgb;

typedef union u_color
{
	unsigned int	color;
	t_rgb			rgb;
}	t_color;

typedef struct s_map_data
{
	char	*north_texture_path;
	char	*south_texture_path;
	char	*west_texture_path;
	char	*east_texture_path;
	char	*door_texture_path;
}	t_map_data;

typedef struct s_texture
{
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
	void		*mlx_img;
	t_img_data	img1;
	t_img_data	img2;
	t_img_data	*current_img;
	t_img_data	*working_img;
}	t_mlx_data;

typedef struct s_display {
	unsigned int	**north_texture;
	unsigned int	**south_texture;
	unsigned int	**west_texture;
	unsigned int	**east_texture;
	unsigned int	**door_texture;
	t_int_vector	north_texture_size;
	t_int_vector	south_texture_size;
	t_int_vector	east_texture_size;
	t_int_vector	west_texture_size;
	int				ray_size[WIN_W];
	int 			pos_x_in_wall[WIN_W];
	int				maze_height;
	int				maze_width;
	char			ray_texture[WIN_W];
	char			**grid_maze;
	t_color			floor_color;
	t_color			ceiling_color;
}	t_display;

typedef struct s_cub3d
{
	// Note: remove map_path from struct
	char		*map_path;
	// Note: remove from struct ??
	char		**map_information;
	t_map_data	map_data;
	t_mlx_data	mlx_data;
	t_display	map_display;
	t_player	player;
}	t_cub3d;

enum e_result
{
	SUCCESS = 0,
	ERROR = 1,
};

#endif
