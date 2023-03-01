/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlitaudo <jlitaudo@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 11:27:24 by jlitaudo          #+#    #+#             */
/*   Updated: 2023/03/01 18:39:26 by jlitaudo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "cub3d.h"
#include "structs.h"

static void set_colum_display(t_cub3d *cube, t_vector player_pos, t_vector ray_direction, int column);

void	raytracer(t_cub3d *cube)
{
	int			y;
	float		relative_pos_in_screen;
	t_vector	ray_direction;
	t_vector	player_dir;
	t_vector	player_pos;

	player_dir = cube->player.dir;
	player_pos = cube->player.pos;
	y = 0;
	while (y < WIN_WIDTH)
	{
		ray_direction.x = -player_dir.y;
		ray_direction.y = player_dir.x;
		relative_pos_in_screen = 2 * y / (double)WIN_WIDTH - 1;// * cube->screen_width;
		ray_direction.x =  ray_direction.x * relative_pos_in_screen + player_dir.x;
		ray_direction.y =  ray_direction.y * relative_pos_in_screen + player_dir.y;
		set_colum_display(cube, player_pos, ray_direction, y);
		y++;
	}
}

static void set_colum_display(t_cub3d *cube, t_vector player_pos, t_vector ray_direction, int column)
{
	int 	map_pos_x;
	int 	map_pos_y;
	int 	step_x;
	int 	step_y;
	t_vector	delta;
	t_vector	side;
	int  	hit;
	int 	wall;

//	dprintf(1, "%f %f \n", ray_direction.x, ray_direction.y);
	map_pos_x = (int)player_pos.x;
	map_pos_y = (int)player_pos.y;
	if (ray_direction.x < 0)
		delta.x = -1 * (1 / ray_direction.x);
	else
		delta.x = 1 / ray_direction.x;
	if (ray_direction.y < 0)
		delta.y = -1 * (1 / ray_direction.y);
	else
		delta.y = -1 / ray_direction.y;
	if (ray_direction.x < 0)
	{
		step_x = -1;
		side.x = (player_pos.x - map_pos_x) * delta.x;
	}
	else
	{
		step_x = 1;
		side.x = (map_pos_x + 1.0f - player_pos.x ) * delta.x;
	}
	if (ray_direction.y < 0)
	{
		step_y = -1;
		side.y = (player_pos.y - map_pos_y) * delta.y;
	}
	else
	{
		step_y = 1;
		side.y = (map_pos_y + 1.0f - player_pos.y ) * delta.y;
	}
	hit = 0;
	while (hit == 0)
	{
		if (side.x < side.y)
		{
			side.x += delta.x;
			map_pos_x += step_x;
			wall = 1;
		}
		else
		{
			side.y += delta.y;
			map_pos_y += step_y;
			wall = 0;
		}
		if (cube->grid_maze[map_pos_y][map_pos_x] == '1')
			hit = 1;
	}
	if (wall == 0)
		cube->raysize[column] = (int) (WIN_HEIGHT / (side.x - delta.x)) ;
	else
		cube->raysize[column] = (int) (WIN_HEIGHT / (side.y - delta.y));
	printf("%f %f %d\n", side.x, side.y, cube->raysize[column]);
}