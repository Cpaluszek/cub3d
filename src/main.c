/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 17:08:15 by jlitaudo          #+#    #+#             */
/*   Updated: 2023/03/03 16:35:43 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "errors.h"

#define PRG_USAGE "Usage: ./cub3D <map.cub>\n"

static void	init_player(t_player *player);

// Todo: missing player parsings
// Todo: ./cub3d maps/ma -> ABORT
// Todo: unclosed map -> mlx is showing
int	main(int argc, char **argv)
{
	t_cub3d	cube;

	if (argc != 2)
		printf(PRG_USAGE);
	cube.map_path = argv[1];
	if (init_mlx_data(&cube.mlx_data) == ERROR)
	{
		printf(ERR_MLX_INIT);
		exit_cube(&cube, ERROR);
	}
	central_parsing(&cube);
//	int i=-1;
//	while (cube.map_display.grid_maze[++i]){
//			printf("%s\n", cube.map_display.grid_maze[i]);
//	}
//	printf("%x %x\n", cube.map_display.ceiling_color.color, cube.map_display.floor_color.color);
	init_player(&cube.player);
	set_mlx_hooks(&cube);
	render(&cube);
	mlx_loop_hook(cube.mlx_data.mlx, &game_loop, &cube);
	mlx_loop(cube.mlx_data.mlx);
	exit_cube(&cube, 0);
	return (SUCCESS);
}

static void	init_player(t_player *player)
{
	player->move.x = 0;
	player->move.y = 0;
	player->rotate = 0;
}
