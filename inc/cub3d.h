/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 13:32:59 by cpalusze          #+#    #+#             */
/*   Updated: 2023/03/02 14:55:45 by cpalusze         ###   ########.fr       */
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

// --- Minimap ---
# define MINI_MAP_X			10
# define MINI_MAP_Y			10
# define MINI_MAP_VIEW_DIST 30
# define MINI_MAP_CELL_SIZE 10
# define MINI_MAP_SIDE_SIZE 300
# define MM_PLAYER_COLOR	0x8AADF4
# define MM_VIEWPORT_COLOR	0xED8796
# define MM_WALL_COLOR		0xCAD3F5
# define MM_BG_COLOR		0x24273A
# define PI					3.1415f
# define SCREEN_DIST	0.1f

// Viewing angle
# define FOV	90

# define LOS_ANGLE 120
# define MAX_LOS	10

//	--- Parsing ---
void			central_parsing(t_cub3d *cube);
void			maze_validity_checking(t_cub3d *cube, char **grid_maze);
void			interpret_map_information(t_cub3d *cube, char **map_info);
void			find_texture_path_and_get_color(t_cub3d *cube, char *line);

// --- MLX ---
enum e_result	init_mlx_data(t_mlx_data *mlx_data);
void			set_mlx_hooks(t_cub3d *cube);

//	--- Game Loop ---
int				game_loop(t_cub3d *cube);

//	--- Render ---
void			init_render(t_cub3d *cube);
void			draw_minimap(t_cub3d *cube);
void			raytracer(t_cub3d *cube);

//	--- Utils ---
void			error_exit_cube(t_cub3d *cube, char *msg1, char *msg2);
void			test_failed_malloc(t_cub3d *cube, void *content);
void			exit_cube(t_cub3d *cube, int exit_code);

#endif