/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_minimap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 10:29:02 by cpalusze          #+#    #+#             */
/*   Updated: 2023/03/01 14:09:46 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_minimap_cell(t_mlx_data *data, int x, int y, int color);
static int	get_cell_color(t_cub3d *cube, int x, int y);

void	draw_minimap(t_cub3d *cube)
{
	t_color		pixel_color;
	int			x;
	int			y;
	int			start_x;
	int			start_y;

	start_x = (int)cube->player.pos.x - MINI_MAP_VIEW_DIST / 2;
	start_y = (int)cube->player.pos.y - MINI_MAP_VIEW_DIST / 2;
	x = start_x;
	while (x < start_x + MINI_MAP_VIEW_DIST)
	{
		y = start_y;
		while (y < start_y + MINI_MAP_VIEW_DIST)
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
	return (MM_BG_COLOR);
}

static void	draw_minimap_cell(t_mlx_data *data, int x, int y, int color)
{
	int	i;
	int	j;
	int	start_x;
	int	start_y;

	start_x = (x * MINI_MAP_CELL_SIZE) + MINI_MAP_X;
	start_y = (y * MINI_MAP_CELL_SIZE) + MINI_MAP_Y;
	i = start_x;
	while (i < start_x + MINI_MAP_CELL_SIZE)
	{
		j = start_y;
		while (j < start_y + MINI_MAP_CELL_SIZE)
		{
			my_mlx_pixel_put(data->working_img, i, j, color);
			j++;
		}
		i++;
	}
}
