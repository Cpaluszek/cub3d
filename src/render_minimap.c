/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_minimap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 10:29:02 by cpalusze          #+#    #+#             */
/*   Updated: 2023/03/09 10:45:57 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "minimap.h"
#include <math.h>


static void	draw_minimap_cell(t_mlx_data *data, int x, int y, int color);
static int	get_cell_color(t_cub3d *cube, int x, int y);
static void	draw_viewport(t_mlx_data *data, t_player player);
static void	draw_line(t_mlx_data *data, t_float_vector p1, t_float_vector p2);

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
	draw_viewport(&cube->mlx_data, cube->player);
	mlx_put_image_to_window(cube->mlx_data.mlx, \
		cube->mlx_data.mlx_win, \
		cube->mlx_data.mlx_img.img, 0, 0);
}

static int	get_cell_color(t_cub3d *cube, int x, int y)
{
	if (x >= 0 && y >= 0 && \
		x < cube->display.maze_size.x && y < cube->display.maze_size.y)
	{
		if (x == (int)cube->player.pos.x && y == (int)cube->player.pos.y)
			return (MM_PLAYER_COLOR);
		else if (cube->display.grid_maze[y][x] == CLOSED_DOOR_CHAR || \
			cube->display.grid_maze[y][x] == OPEN_DOOR_CHAR)
			return (MM_DOOR_COLOR);
		else if (cube->display.grid_maze[y][x] == WALL_CHAR)
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
			my_mlx_pixel_put(&data->mlx_img, i, j, color);
			j++;
		}
		i++;
	}
}

static void	draw_viewport(t_mlx_data *data, t_player player)
{
	t_float_vector	start;
	t_float_vector	end;
	float			map_center;

	map_center = MINI_MAP_SIDE_SIZE / 2.0 + MINI_MAP_CELL_SIZE / 2.0;
	start.x = MINI_MAP_X + map_center;
	start.y = MINI_MAP_Y + map_center;
	end.x = start.x + 50 * (float) cos(player.angle - M_PI_4);
	end.y = start.y + 50 * (float) sin(player.angle - M_PI_4);
	draw_line(data, start, end);
	end.x = start.x + 50 * (float) cos(player.angle + M_PI_4);
	end.y = start.y + 50 * (float) sin(player.angle + M_PI_4);
	draw_line(data, start, end);
}

static void	draw_line(t_mlx_data *data, t_float_vector p1, t_float_vector p2)
{
	t_float_vector	delta;
	float			max;

	delta.x = p2.x - p1.x;
	delta.y = p2.y - p1.y;
	max = fmaxf(fabsf(delta.x), fabsf(delta.y));
	delta.x /= max;
	delta.y /= max;
	while (((int)(p1.x - p2.x) || (int)(p1.y - p2.y)))
	{
		my_mlx_pixel_put(&data->mlx_img, (int)p1.x, (int)p1.y, \
			MM_VIEWPORT_COLOR);
		p1.x += delta.x;
		p1.y += delta.y;
	}
}
