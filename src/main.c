/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 17:08:15 by jlitaudo          #+#    #+#             */
/*   Updated: 2023/03/08 12:59:35 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "errors.h"

#define PRG_USAGE "Usage: ./cub3D <map.cub>\n"

static void	init_player(t_player *player);

int	main(int argc, char **argv)
{
	t_cub3d	cube;

	if (argc != 2)
		printf(PRG_USAGE);
	cube.map_path = argv[1];
	central_parsing(&cube);
	if (init_mlx_data(&cube.mlx_data) == ERROR)
	{
		printf(ERR_MLX_INIT);
		exit_cube(&cube, ERROR);
	}
	create_texture_array(&cube);
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
	player->attack_state = 0;
}
