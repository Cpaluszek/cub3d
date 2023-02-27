/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Teiki <Teiki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 13:32:59 by cpalusze          #+#    #+#             */
/*   Updated: 2023/02/27 16:57:39 by Teiki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <errno.h>
# include "libft.h"
# include "../lib/minilibx-linux/mlx.h"

# define LOS_ANGLE 120
# define MAX LOS	10

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
}t_color;

typedef struct s_map
{
	char	*north_texture;
	char	*south_texture;
	char	*west_texture;
	char	*east_texture;
	t_color	floor_color;
	t_color	ceiling_color;
}t_map;

typedef struct s_general
{
	char	*map_path;
	short	**grid_maze;
	t_map	map_display;
	int		view_angle;
}t_general;

# define WIN_WIDTH	1920
# define WIN_HEIGHT	1080
# define WIN_NAME	"cub3D"

# define ERR_MALLOC "Error with malloc(3)"

# define ERR_PATH "Error opening map file : "
# define INVALID_FILE_PARAM "Error in file : \
	unrecognized input parameter at line : "
# define INVALID_TEXT_FILE_PATTERN "Invalid texture pattern at line : "
# define EMPTY_PATTERN "Pattern is empty at line : "
# define INVALID_COLOR "Invalid color input at line : "

enum e_result
{
	SUCCESS = 0,
	ERROR = 1,
	FINISHED = 10,
};

void	find_texture_path_and_get_color(t_general *cube, char *line);

void	error_exit_cube(t_general *cube, char *msg1, char *msg2);
void	test_failed_malloc(t_general *cube, void *content);
void	exit_cube(t_general *cube, int exit_code);

#endif