/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 13:32:59 by cpalusze          #+#    #+#             */
/*   Updated: 2023/03/09 13:15:39 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include "libft.h"

# define WIN_W	1920
# define WIN_H	1080
# define WIN_NAME	"cub3D"

# define TORCH_IDLE_TEX_PATH "textures/torch.xpm"
# define TORCH_ATTACK_TEX_PATH "textures/attack_torch.xpm"

# define DOOR_TEX_PATH "textures/door.xpm"

# define GRID_CHARSET "01NSEW Dd"
# define PLAYER_START_CHARSET "NSEW"
# define MAZE_CHARSET "0NSEW"
# define WALL_CHAR '1'
# define EMPTY_CHAR '0'
# define CLOSED_DOOR_CHAR 'D'
# define OPEN_DOOR_CHAR 'd'
# define NO_COLLISION_CHARSET "0d"
# define COLLISION_CHARSET "1D"

# include "structs.h"

# define SCREEN_DIST		0.1f
# define ROT_SPEED			0.01f
# define MOUSE_ROT_SPEED	0.062831f

//	--- Parsing ---
void			central_parsing(t_cub3d *cube, char *map_path);
void			maze_validity_checking(t_cub3d *cube, char **grid_maze);
void			interpret_map_information(t_cub3d *cube, char **map_info);
void			find_texture_path_and_get_color(t_cub3d *cube, char *line);
void			create_texture_array(t_cub3d *cube);

// --- MLX ---
enum e_result	init_mlx_data(t_mlx_data *mlx_data);
void			set_mlx_hooks(t_cub3d *cube);
int				mouse_move_hook(int x, int y, t_cub3d *cube);
int				mouse_down_hook(int button, int x, int y, t_cub3d *cube);
int				mouse_up_hook(int button, int x, int y, t_cub3d *cube);

//	--- Game Loop ---
int				game_loop(t_cub3d *cube);

//	--- Render ---
void			render(t_cub3d *cube);
void			draw_minimap(t_cub3d *cube);
void			raytracer(t_cub3d *cube);
void			fill_col_display(t_cub3d *cube, t_ray *ray,
					int is_wall_hit_on_x_axis, int col);
void			draw_torch(t_cub3d *cube);

//	--- Utils ---
void			error_exit_cube(t_cub3d *cube, char *msg1, char *msg2);
void			test_failed_malloc(t_cub3d *cube, void *content);
void			exit_cube(t_cub3d *cube, int exit_code);

#endif