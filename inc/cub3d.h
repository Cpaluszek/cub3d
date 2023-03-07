/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlitaudo <jlitaudo@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 13:32:59 by cpalusze          #+#    #+#             */
/*   Updated: 2023/03/06 19:29:30 by jlitaudo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include "libft.h"

# define WIN_W	1920
# define WIN_H	1080
# define WIN_NAME	"cub3D"

# define TORCH_TEX_PATH "textures/torch.xpm"
# define TORCH_ATTACK_TEX_PATH "textures/attack_torch.xpm"

# include "structs.h"

// Todo: use a header for minimap infos
// --- Minimap ---
# define MINI_MAP_X			10
# define MINI_MAP_Y			10
# define MINI_MAP_VIEW_DIST 40
# define MINI_MAP_CELL_SIZE 6
# define MINI_MAP_SIDE_SIZE 240
# define MM_PLAYER_COLOR	0x8AADF4
# define MM_VIEWPORT_COLOR	0xED8796
# define MM_WALL_COLOR		0xCAD3F5
# define MM_BG_COLOR		0x24273A

// --- Player ---
# define SCREEN_DIST		0.1f
# define ROT_SPEED			0.01f
# define MOUSE_ROT_SPEED	0.062831f

//	--- Parsing ---
void			central_parsing(t_cub3d *cube);
void			maze_validity_checking(t_cub3d *cube, char **grid_maze);
void			interpret_map_information(t_cub3d *cube, char **map_info);
void			find_texture_path_and_get_color(t_cub3d *cube, char *line);
void			create_texture_array(t_cub3d *cube);

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