/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 13:32:59 by cpalusze          #+#    #+#             */
/*   Updated: 2023/02/28 13:49:36 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <errno.h>
# include "libft.h"
# include "mlx_utils.h"
# include "../lib/minilibx-linux/mlx.h"

# define LOS_ANGLE 120
# define MAX_LOS	10

typedef struct s_rgb
{
	unsigned char	blu;
	unsigned char	gre;
	unsigned char	red;
}t_rgb;

typedef union u_color
{
	unsigned int	color;
	t_rgb			rgb;
}	t_color;

typedef struct s_map
{
	char	*north_texture;
	char	*south_texture;
	char	*west_texture;
	char	*east_texture;
	t_color	floor_color;
	t_color	ceiling_color;
}	t_map;

typedef struct	s_mlx_data {
	void		*mlx;
	void		*mlx_win;
	void		*mlx_img;
	t_img_data	imgData;
}	t_mlx_data;

typedef struct s_cub3d
{
	char		*map_path;
	char		**grid_maze;
	t_map		map_display;
	int			view_angle;
	t_mlx_data	mlx_data;
}	t_cub3d;

# define WIN_WIDTH	1920
# define WIN_HEIGHT	1080
# define WIN_NAME	"cub3D"

# define ERR_MALLOC "Error with malloc(3)"

# define ERR_PATH "Map file : "
# define INVALID_FILE_PARAM "Unrecognized input parameter at line : "
# define INVALID_TEXT_FILE_PATTERN "Invalid texture pattern at line : "
# define EMPTY_PATTERN "Pattern is empty at line : "
# define INVALID_COLOR "Invalid color input at line : "

enum e_result
{
	SUCCESS = 0,
	ERROR = 1,
	FINISHED = 10,
};

//	--- Parsing ---
void	central_parsing(t_cub3d *cube);
void	find_texture_path_and_get_color(t_cub3d *cube, char *line);

// --- MLX ---
enum e_result	init_mlx_data(t_mlx_data *mlx_data);
void			set_mlx_hooks(t_mlx_data *mlx_data);

//	--- Utils ---
void	error_exit_cube(t_cub3d *cube, char *msg1, char *msg2);
void	test_failed_malloc(t_cub3d *cube, void *content);
void	exit_cube(t_cub3d *cube, int exit_code);


// _-- Debug
void print_maze(char **maze);

#endif