/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlitaudo <jlitaudo@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 14:51:59 by cpalusze          #+#    #+#             */
/*   Updated: 2023/03/03 11:41:20 by jlitaudo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "mlx_utils.h"
# include "cub3d.h"

// Todo: double or float ?
typedef struct s_vector {
	float	x;
	float	y;
}	t_vector;

typedef struct s_player {
	t_vector	pos;
	t_vector	dir;
	// Todo: use int instead of float ?
	t_vector	move;
	float		rotate;
	float		angle;
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
	t_color	floor_color;
	t_color	ceiling_color;
	int		height;
	int		width;
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
	int				raysize[1920];
	int				maze_height;
	int				maze_width;
	char			raytexture[1920];
	char			**grid_maze;
	t_color			floor_color;
	t_color			ceiling_color;
}t_display;

typedef struct s_cub3d
{
	// Note: remove map_path from struct
	char		*map_path;
	char		**grid_maze;
	// Note: remove from struct ??
	char		**map_information;
	t_map_data	map_data;
	t_mlx_data	mlx_data;
	t_display	map_display;
	t_player	player;
	// Note: try to use previous defines
	int			raysize[1920];
	char		raytexture[1920];
}	t_cub3d;

enum e_result
{
	SUCCESS = 0,
	ERROR = 1,
};

#endif
