/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 09:50:14 by cpalusze          #+#    #+#             */
/*   Updated: 2023/03/08 13:15:27 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_maze(t_cub3d *cube);
static int	retrieve_color(t_display *map_display, int x, int y, int diff);
static int get_relative_y(t_display *map_display, int x, int y, int diff);

void	render(t_cub3d *cube)
{
	raytracer(cube);
	draw_maze(cube);
	draw_minimap(cube);
	// Todo: draw torch
	draw_torch(cube);
}

static void	draw_maze(t_cub3d *cube)
{
	t_mlx_data	data;
	t_display	*map_display;
	int 		diff;
	t_int_vector pos;

	data = cube->mlx_data;
	map_display = &cube->display;
	pos.x = 0;
	while (pos.x < WIN_W)
	{
		pos.y = 0;
		diff = (WIN_H - map_display->ray_size[pos.x]) / 2;
		while (pos.y < WIN_H)
		{
			my_mlx_pixel_put(&data.mlx_img, pos.x, pos.y, retrieve_color(map_display, pos.x, pos.y, diff));
			pos.y++;
		}
		pos.x++;
	}
	mlx_put_image_to_window(data.mlx, data.mlx_win, \
		data.mlx_img.img, 0, 0);
}

static int retrieve_color(t_display *map_display, int x, int y, int diff)
{
	int relative_y;

	if (y < diff)
		return (map_display->ceiling_color.color);
	if (diff < 0 || y < (WIN_H - diff ))
	{
		relative_y = get_relative_y(map_display, x, y, diff);
		if (map_display->ray_texture[x] == 'N')
			return (map_display->north_texture[relative_y][map_display->wall_pos_x[x]]);
		else if (map_display->ray_texture[x] == 'S')
			return (map_display->south_texture[relative_y][map_display->wall_pos_x[x]]);
		else if (map_display->ray_texture[x] == 'W')
			return (map_display->west_texture[relative_y][map_display->wall_pos_x[x]]);
		else if (map_display->ray_texture[x] == 'E')
			return (map_display->east_texture[relative_y][map_display->wall_pos_x[x]]);
	}
	return (map_display->floor_color.color);
}

static int get_relative_y(t_display *map_display, int x, int y, int diff)
{
	int relative_y;
	int y_size;

	y_size = 0;
	if (map_display->ray_texture[x] == 'N')
		y_size = map_display->north_texture_size.y;
	else if (map_display->ray_texture[x] == 'S')
		y_size = map_display->south_texture_size.y;
	else if (map_display->ray_texture[x] == 'W')
		y_size = map_display->west_texture_size.y;
	else if (map_display->ray_texture[x] == 'E')
		y_size = map_display->east_texture_size.y;
	relative_y = (int)((float)((float)(y - diff) / ((float)map_display->ray_size[x])) * (float)y_size);
	relative_y %= y_size;
	return (relative_y);
}
