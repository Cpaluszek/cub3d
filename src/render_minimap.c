/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_minimap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 10:29:02 by cpalusze          #+#    #+#             */
/*   Updated: 2023/03/01 13:31:04 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define MM_SCALE 15

static void	draw_minimap_cell(t_mlx_data *data, int x, int y, int color);
static int	get_cell_color(t_cub3d *cube, int x, int y);

void	draw_minimap(t_cub3d *cube)
{
	t_color		pixel_color;
	int			x;
	int			y;
	int			start_x;
	int			start_y;

	for (int i = 0; i < 320; i++)
	{
		my_mlx_pixel_put(cube->mlx_data.working_img, 310, i, 0xFFFFFF);
		my_mlx_pixel_put(cube->mlx_data.working_img, 10, i, 0xFFFFFF);
	}
	for (int i = 0; i < 320; i++)
	{
		my_mlx_pixel_put(cube->mlx_data.working_img, i, 10, 0xFFFFFF);
		my_mlx_pixel_put(cube->mlx_data.working_img, i, 310, 0xFFFFFF);
	}

	start_x = (int)cube->player.pos.x - MM_SCALE;
	start_y = (int)cube->player.pos.y - MM_SCALE;
	x = start_x;
	while (x < start_x + 2 * MM_SCALE)
	{
		y = start_y;
		while (y < start_y + 2 * MM_SCALE)
		{
			pixel_color.color = get_cell_color(cube, x, y);
			draw_minimap_cell(&cube->mlx_data, x - start_x, \
				y - start_y, pixel_color.color);
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(cube->mlx_data.mlx, \
		cube->mlx_data.mlx_win, \
		cube->mlx_data.working_img->img, 0, 0);
}

static int	get_cell_color(t_cub3d *cube, int x, int y)
{
	if (x >= 0 && y >= 0 && \
		x < cube->map_data.width && y < cube->map_data.height)
	{
		if (x == (int)cube->player.pos.x && y == (int)cube->player.pos.y)
			return (MM_PLAYER_COLOR);
		else if (cube->grid_maze[y][x] == '1')
			return (MM_WALL_COLOR);
	}
	return (MM_BACKGROUND_COLOR);
}

static void	draw_minimap_cell(t_mlx_data *data, int x, int y, int color)
{
	int	i;
	int	j;
	int	start_x;
	int	start_y;

	start_x = (x * MM_SCALE / 2) + MINI_MAP_X;
	start_y = (y * MM_SCALE / 2) + MINI_MAP_Y;
	i = start_x;
	while (i < start_x + MM_SCALE)
	{
		j = start_y;
		while (j < start_y + MM_SCALE)
		{
			my_mlx_pixel_put(data->working_img, i, j, color);
			j++;
		}
		i++;
	}
}
