/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 09:50:14 by cpalusze          #+#    #+#             */
/*   Updated: 2023/03/01 10:15:48 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_minimap(t_cub3d *cube);

void	init_render(t_cub3d *cube)
{
	// Draw minimap
	(void) cube;
	cube->mlx_data.working_img = &cube->mlx_data.img1;
	draw_minimap(cube);
}

void	draw_minimap(t_cub3d *cube)
{
	t_mlx_data	data;
	int			x;
	int			y;

	data = cube->mlx_data;
	y = MINI_MAP_Y;
	while (y < MINI_MAP_HEIGHT + MINI_MAP_Y)
	{
		x = MINI_MAP_X;
		while (x < MINI_MAP_WIDTH + MINI_MAP_X)
		{
			// Wall ?

			// Player ?

			my_mlx_pixel_put(data.working_img, x, y, 0xFFFFFF);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(data.mlx, data.mlx_win, data.working_img->img, 0, 0);
}