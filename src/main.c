/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 17:08:15 by jlitaudo          #+#    #+#             */
/*   Updated: 2023/03/01 09:52:56 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Todo: Makefile lib compilation check

int	main(int argc, char **argv)
{
    t_cub3d cube;

	if (argc != 2)
		printf("Usage: ./cub3D <map.cub>\n");
    cube.map_path = argv[1];
	central_parsing(&cube);
	if (init_mlx_data(&cube.mlx_data) == ERROR)
	{
		// Todo: free
		return (ERROR);
	}
	set_mlx_hooks(&cube);
	init_render(&cube);
	mlx_loop(cube.mlx_data.mlx);
	return (SUCCESS);
}
