/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 13:32:59 by cpalusze          #+#    #+#             */
/*   Updated: 2023/03/01 10:18:43 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include "structs.h"
# include "libft.h"
# include "mlx_utils.h"

# define WIN_WIDTH	1920
# define WIN_HEIGHT	1080
# define WIN_NAME	"cub3D"

# define MINI_MAP_X 10
# define MINI_MAP_Y 10
# define MINI_MAP_WIDTH 300
# define MINI_MAP_HEIGHT 300

// Viewing angle
# define FOV	120

# define LOS_ANGLE 120
# define MAX_LOS	10

//	--- Parsing ---
void	central_parsing(t_cub3d *cube);
void	maze_validity_checking(t_cub3d *cube, char **grid_maze);
void	interpret_map_information(t_cub3d *cube, char **map_information);
void	find_texture_path_and_get_color(t_cub3d *cube, char *line);

// --- MLX ---
enum e_result	init_mlx_data(t_mlx_data *mlx_data);
void			set_mlx_hooks(t_cub3d *cube);

// --- Render ---

void	init_render(t_cub3d *cube);


//	--- Utils ---
void	error_exit_cube(t_cub3d *cube, char *msg1, char *msg2);
void	test_failed_malloc(t_cub3d *cube, void *content);
void	exit_cube(t_cub3d *cube, int exit_code);

// _-- Debug
void print_maze(char **maze);

#endif