/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlitaudo <jlitaudo@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 17:08:15 by jlitaudo          #+#    #+#             */
/*   Updated: 2023/02/23 18:40:52 by jlitaudo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int   printkey(int key);

int	main(int argc, char **argv)
{
	(void) argc;
    void *mlx_ptr;
    void *win_ptr;
    t_general cube;

    cube.map_path = argv[1];
//    mlx_ptr = mlx_init();
//    win_ptr = mlx_new_window(mlx_ptr, 200, 200, argv[0]);
	printf("%s\n", argv[0]);
//    mlx_key_hook(win_ptr, printkey, NULL);
//    mlx_loop(mlx_ptr);
	return (SUCCESS);
}

int   printkey(int key)
{
    return (printf("%d\n", key));
}