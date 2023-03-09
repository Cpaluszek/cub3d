/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_col_display.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 14:36:13 by cpalusze          #+#    #+#             */
/*   Updated: 2023/03/09 14:41:49 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	manage_x_axis(t_cub3d *cube, t_ray *ray, int col);
static void	manage_y_axis(t_cub3d *cube, t_ray *ray, int col);

void	fill_col_display(t_cub3d *cube, t_ray *ray, \
	int is_wall_hit_on_x_axis, int col)
{
	if (is_wall_hit_on_x_axis == 0)
	{
		manage_x_axis(cube, ray, col);
	}
	else
	{
		manage_y_axis(cube, ray, col);
	}
	ray->relative_wall_hit -= (int)ray->relative_wall_hit;
	if (ray->relative_wall_hit < 0)
		ray->relative_wall_hit *= -1;
}

static void	manage_x_axis(t_cub3d *cube, t_ray *ray, int col)
{
	cube->display.ray_size[col] = (int)(WIN_H / \
			(ray->closest_wall.x - ray->next_wall_hit.x));
	ray->relative_wall_hit = (ray->closest_wall.x - ray->next_wall_hit.x) * \
			ray->direction.y + cube->player.pos.y;
	if (cube->display.grid_maze[ray->map_pos.y][ray->map_pos.x] == \
			CLOSED_DOOR_CHAR)
		cube->display.ray_texture[col] = CLOSED_DOOR_CHAR;
	else if (ray->moving_direction.x < 0)
		cube->display.ray_texture[col] = 'W';
	else
		cube->display.ray_texture[col] = 'E';
}

static void	manage_y_axis(t_cub3d *cube, t_ray *ray, int col)
{
	cube->display.ray_size[col] = (int)(WIN_H / \
			(ray->closest_wall.y - ray->next_wall_hit.y));
	ray->relative_wall_hit = (ray->closest_wall.y - ray->next_wall_hit.y) * \
			ray->direction.x + cube->player.pos.x;
	if (cube->display.grid_maze[ray->map_pos.y][ray->map_pos.x] == \
			CLOSED_DOOR_CHAR)
		cube->display.ray_texture[col] = CLOSED_DOOR_CHAR;
	else if (ray->moving_direction.y < 0)
		cube->display.ray_texture[col] = 'N';
	else
		cube->display.ray_texture[col] = 'S';
}
