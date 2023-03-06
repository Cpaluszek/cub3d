/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlitaudo <jlitaudo@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 09:50:14 by cpalusze          #+#    #+#             */
/*   Updated: 2023/03/06 19:26:04 by jlitaudo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_maze(t_cub3d *cube);
static unsigned int	retrieve_color(t_display *map_display, int x, int y, int diff);

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
	t_display	*map_display;
	int 		diff;
	int			x;
	int			y;

	data = cube->mlx_data;
	map_display = &cube->map_display;
	x = 0;
	while (x < WIN_W)
	{
		y = 0;
		diff = (WIN_H - map_display->raysize[x]) / 2;
//		dprintf(1, " %d - diff=%d\n", map_display->pos_x_in_wall[x],diff);
		while (y < WIN_H)
		{
			my_mlx_pixel_put(data.working_img, x, y, retrieve_color(map_display, x, y, diff));
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(data.mlx, data.mlx_win, \
		data.working_img->img, 0, 0);
}

static unsigned int retrieve_color(t_display *map_display, int x, int y, int diff)
{
	int relative_y_in_texture;

	if (y < diff)
		return (map_display->ceiling_color.color);
	if (diff < 0 || y < (WIN_H - diff ))
	{
		//todo adapter a la taile de la texture.
		relative_y_in_texture = (int)((float)((float)(y - diff) / ((float)map_display->raysize[x])) * 64);
		if (relative_y_in_texture >= 64)
			relative_y_in_texture = 63;
		if (map_display->raytexture[x] == 'N')
			return (map_display->north_texture[relative_y_in_texture][map_display->pos_x_in_wall[x]]);
		else if (map_display->raytexture[x] == 'S')
			return (map_display->south_texture[relative_y_in_texture][map_display->pos_x_in_wall[x]]);
		else if (map_display->raytexture[x] == 'W')
			return (map_display->west_texture[relative_y_in_texture][map_display->pos_x_in_wall[x]]);
		else if (map_display->raytexture[x] == 'E')
			return (map_display->east_texture[relative_y_in_texture][map_display->pos_x_in_wall[x]]);
	}
	return (map_display->floor_color.color);
}
