/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 17:08:15 by jlitaudo          #+#    #+#             */
/*   Updated: 2023/03/10 11:03:49 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "errors.h"

#define PRG_USAGE "Usage: ./cub3D <map.cub>\n"
#define DEFAULT_COLOR_VALUE 0x01000000

static void	set_default_values(t_cub3d *cube);
static void	init_player(t_player *player);

int	main(int argc, char **argv)
{
	t_cub3d	cube;

	if (argc != 2)
		printf(PRG_USAGE);
	set_default_values(&cube);
	central_parsing(&cube, argv[1]);
	if (init_mlx_data(&cube.mlx_data) == ERROR)
	{
		printf(ERR_MLX_INIT);
		exit_cube(&cube, ERROR);
	}
	create_texture_array(&cube);
	set_mlx_hooks(&cube);
	render(&cube);
	mlx_loop_hook(cube.mlx_data.mlx, &game_loop, &cube);
	mlx_loop(cube.mlx_data.mlx);
	exit_cube(&cube, 0);
	return (SUCCESS);
}

static void	set_default_values(t_cub3d *cube)
{
	cube->textures_paths.north_texture_path = NULL;
	cube->textures_paths.south_texture_path = NULL;
	cube->textures_paths.west_texture_path = NULL;
	cube->textures_paths.east_texture_path = NULL;
	cube->display.grid_maze = NULL;
	cube->display.ceiling_color.color = DEFAULT_COLOR_VALUE;
	cube->display.floor_color.color = DEFAULT_COLOR_VALUE;
	cube->display.north_tex.content = NULL;
	cube->display.south_tex.content = NULL;
	cube->display.east_tex.content = NULL;
	cube->display.west_tex.content = NULL;
	cube->display.torch_idle_tex.content = NULL;
	cube->display.torch_attack_tex.content = NULL;
	cube->display.door_tex.content = NULL;
	cube->mlx_data.mlx = NULL;
	cube->mlx_data.mlx_win = NULL;
	cube->mlx_data.mlx_img.img = NULL;
	init_player(&cube->player);
}

static void	init_player(t_player *player)
{
	player->pos.x = 0.0f;
	player->pos.y = 0.0f;
	player->move.x = 0;
	player->move.y = 0;
	player->rotate = 0;
	player->attack_state = 0;
}
