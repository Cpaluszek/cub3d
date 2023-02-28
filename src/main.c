/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 17:08:15 by jlitaudo          #+#    #+#             */
/*   Updated: 2023/02/28 10:08:33 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//int   printkey(int key);

int	main(int argc, char **argv)
{
//    void *mlx_ptr;
//    void *win_ptr;
    t_cub3d cube;

	if (argc != 2)
		printf("Usage: ./cub3D <map.cub>\n");
    cube.map_path = argv[1];
	central_parsing(&cube);
//    mlx_ptr = mlx_init();
//    win_ptr = mlx_new_window(mlx_ptr, 200, 200, argv[0]);
//    mlx_key_hook(win_ptr, printkey, NULL);
//    mlx_loop(mlx_ptr);
	return (SUCCESS);
}
//
//int   printkey(int key)
//{
//    return (printf("%d\n", key));
//}