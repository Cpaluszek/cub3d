/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 17:08:15 by jlitaudo          #+#    #+#             */
/*   Updated: 2023/02/28 15:16:21 by cpalusze         ###   ########.fr       */
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
	for (int i = 100; i < WIN_WIDTH - 100; i++)
	{
		my_mlx_pixel_put(&cube.mlx_data.img, i, 100, 0x00FF00FF);
	}
	mlx_put_image_to_window(cube.mlx_data.mlx, cube.mlx_data.mlx_win, cube.mlx_data.img.img, 0, 0);
	mlx_loop(cube.mlx_data.mlx);
	return (SUCCESS);
}
