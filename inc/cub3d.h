/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlitaudo <jlitaudo@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 13:32:59 by cpalusze          #+#    #+#             */
/*   Updated: 2023/02/28 14:36:38 by jlitaudo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <errno.h>
# include "libft.h"
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

typedef struct s_cub3d
{
	char	*map_path;
	char	**grid_maze;
	t_map	map_display;
	int		view_angle;
}	t_cub3d;

# define WIN_WIDTH	1920
# define WIN_HEIGHT	1080
# define WIN_NAME	"cub3D"

# define ERR_MALLOC "Error with malloc(3)"
# define ERR_READ "Error reading file"

# define ERR_PATH "Map file : "
# define ERR_FORMAT "Invalid map format, must be \"*.cub\""
# define INVALID_PATTERN "Invalid file pattern"
# define INVALID_FILE_PARAM "Unrecognized or duplicated input parameter at line : "
# define INVALID_TEXT_FILE_PATTERN "Invalid texture pattern at line : "
# define EMPTY_PATTERN "Pattern is empty at line : "
# define INVALID_COLOR "Invalid color input at line : "
# define INVALID_MAZE_CHAR "Unrecognized character in maze at line : "
# define UNCLOSED_MAZE "Unclosed maze at line : "
# define SPAWNING "Missing of / too many spawning point "

enum e_result
{
	SUCCESS = 0,
	ERROR = 1,
	FINISHED = 10,
};

//	--- Parsing ---
void	central_parsing(t_cub3d *cube);
void	maze_validity_checking(t_cub3d *cube, char **grid_maze);
void	find_texture_path_and_get_color(t_cub3d *cube, char *line);


//	--- Utils ---
void	error_exit_cube(t_cub3d *cube, char *msg1, char *msg2);
void	test_failed_malloc(t_cub3d *cube, void *content);
void	exit_cube(t_cub3d *cube, int exit_code);


// _-- Debug
void print_maze(char **maze);

#endif