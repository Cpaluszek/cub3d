/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 09:50:14 by cpalusze          #+#    #+#             */
/*   Updated: 2023/03/02 15:28:48 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_maze(t_cub3d *cube);
static int	retrieve_color(t_cub3d *cube, int x, int y);

void	init_render(t_cub3d *cube)
{
	cube->mlx_data.working_img = &cube->mlx_data.img1;
	raytracer(cube);
	draw_maze(cube);
	draw_minimap(cube);
}

static void	draw_maze(t_cub3d *cube)
{
	t_mlx_data	data;
	int			color;
	int			x;
	int			y;

	data = cube->mlx_data;
	x = 0;
	while (x < WIN_W)
	{
		y = 0;
		while (y < WIN_H)
		{
			color = retrieve_color(cube, x, y);
			my_mlx_pixel_put(data.working_img, x, y, color);
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(data.mlx, data.mlx_win, \
		data.working_img->img, 0, 0);
}

static int	retrieve_color(t_cub3d *cube, int x, int y)
{
	int	column_size;
	int	diff;

	column_size = cube->raysize[x];
	diff = (WIN_H - column_size) / 2;
	if (diff < 0)
	{
		if (cube->raytexture[x] == 'N')
			return (0xFFAA00);
		else if (cube->raytexture[x] == 'S')
			return (0x77FF00);
		else if (cube->raytexture[x] == 'W')
			return (0x11AA55);
		else if (cube->raytexture[x] == 'E')
			return (0x00FF99);
	}
	if (y < diff)
		return (cube->map_data.ceiling_color.color);
	else if (y < (WIN_H - diff))
	{
		if (cube->raytexture[x] == 'N')
			return (0xFFAA00);
		else if (cube->raytexture[x] == 'S')
			return (0x77FF00);
		else if (cube->raytexture[x] == 'W')
			return (0x11AA55);
		else if (cube->raytexture[x] == 'E')
			return (0x00FF99);
	}
	return (cube->map_data.floor_color.color);
}
