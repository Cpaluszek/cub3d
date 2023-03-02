/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 11:27:24 by jlitaudo          #+#    #+#             */
/*   Updated: 2023/03/02 15:22:25 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "structs.h"

static void	set_col_display(t_cub3d *cube, t_vector player_pos, \
	t_vector ray_dir, int col);

void	raytracer(t_cub3d *cube)
{
	int			y;
	float		relative_pos_in_screen;
	t_vector	ray_direction;
	t_vector	p_dir;
	t_vector	p_pos;

	p_dir = cube->player.dir;
	p_pos = cube->player.pos;
	y = 0;
	while (y < WIN_W)
	{
		ray_direction.x = -p_dir.y;
		ray_direction.y = p_dir.x;
		relative_pos_in_screen = 2 * y / (double)WIN_W - 1;
		ray_direction.x = ray_direction.x * relative_pos_in_screen + p_dir.x;
		ray_direction.y = ray_direction.y * relative_pos_in_screen + p_dir.y;
		set_col_display(cube, p_pos, ray_direction, y);
		y++;
	}
}

static void	set_col_display(t_cub3d *cube, t_vector player_pos, \
	t_vector ray_dir, int col)
{
	int			map_pos_x;
	int			map_pos_y;
	int			step_x;
	int			step_y;
	t_vector	delta;
	t_vector	side;
	int			hit;
	int			wall;

	map_pos_x = (int)player_pos.x;
	map_pos_y = (int)player_pos.y;
	if (ray_dir.x < 0)
		delta.x = -1 * (1 / ray_dir.x);
	else
		delta.x = 1 / ray_dir.x;
	if (ray_dir.y < 0)
		delta.y = -1 * (1 / ray_dir.y);
	else
		delta.y = 1 / ray_dir.y;
	if (ray_dir.x < 0)
	{
		step_x = -1;
		side.x = (player_pos.x - map_pos_x) * delta.x;
	}
	else
	{
		step_x = 1;
		side.x = (map_pos_x + 1.0f - player_pos.x) * delta.x;
	}
	if (ray_dir.y < 0)
	{
		step_y = -1;
		side.y = (player_pos.y - map_pos_y) * delta.y;
	}
	else
	{
		step_y = 1;
		side.y = (map_pos_y + 1.0f - player_pos.y) * delta.y;
	}
	hit = 0;
	while (hit == 0)
	{
		if (side.x < side.y)
		{
			side.x += delta.x;
			map_pos_x += step_x;
			wall = 0;
		}
		else
		{
			side.y += delta.y;
			map_pos_y += step_y;
			wall = 1;
		}
		if (cube->grid_maze[map_pos_y][map_pos_x] == '1')
			hit = 1;
	}
	if (wall == 0)
	{
		cube->raysize[col] = (int)(WIN_H / (side.x - delta.x));
		if (step_x < 0)
			cube->raytexture[col] = 'W';
		else
			cube->raytexture[col] = 'E';
	}
	else
	{
		cube->raysize[col] = (int)(WIN_H / (side.y - delta.y));
		if (step_y < 0)
			cube->raytexture[col] = 'N';
		else
			cube->raytexture[col] = 'S';
	}
}
