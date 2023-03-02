/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 17:08:15 by jlitaudo          #+#    #+#             */
/*   Updated: 2023/03/02 15:14:39 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define PRG_USAGE "Usage: ./cub3D <map.cub>\n"

static void	init_player(t_player *player);

// Todo: Makefile lib compilation check
int	main(int argc, char **argv)
{
	t_cub3d	cube;

	if (argc != 2)
		printf(PRG_USAGE);
	cube.map_path = argv[1];
	central_parsing(&cube);
	if (init_mlx_data(&cube.mlx_data) == ERROR)
	{
		// Todo: free
		return (ERROR);
	}
	init_player(&cube.player);
	set_mlx_hooks(&cube);
	init_render(&cube);
	mlx_loop_hook(cube.mlx_data.mlx, &game_loop, &cube);
	mlx_loop(cube.mlx_data.mlx);
	return (SUCCESS);
}

static void	init_player(t_player *player)
{
	player->move.x = 0;
	player->move.y = 0;
	player->rotate = 0;
}
