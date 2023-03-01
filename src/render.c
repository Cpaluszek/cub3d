/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlitaudo <jlitaudo@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 09:50:14 by cpalusze          #+#    #+#             */
/*   Updated: 2023/03/01 17:09:54 by jlitaudo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_minimap(t_cub3d *cube);
static void	draw_maze(t_cub3d *cube);
static int retrieve_color(t_cub3d *cube, int x, int y);

void	init_render(t_cub3d *cube)
{
	cube->mlx_data.working_img = &cube->mlx_data.img1;
	raytracer(cube);
	draw_maze(cube);
	draw_minimap(cube);
}

static void	draw_maze(t_cub3d *cube)
{
	int x;
	int y;

	x = 0;
	while (x < WIN_WIDTH)
	{
		y = 0;
		while ( y < WIN_HEIGHT)
		{
			my_mlx_pixel_put(cube->mlx_data.working_img, x, y, retrieve_color(cube, x, y));
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(cube->mlx_data.mlx, cube->mlx_data.mlx_win, cube->mlx_data.working_img->img, 0, 0);
}

static int retrieve_color(t_cub3d *cube, int x, int y)
{
	int column_size;
	int diff;

	column_size = cube->raysize[x];
	diff = (WIN_HEIGHT - column_size) / 2;
	if (diff < 0)
		return (0xFFFFFF);
	else if (y < diff)
		return (cube->map_data.ceiling_color.color);
	else if (y < (WIN_HEIGHT + diff))
		return (0xFFFFFF);
	else
		return (cube->map_data.floor_color.color);
}