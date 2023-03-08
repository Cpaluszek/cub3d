/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 11:27:24 by jlitaudo          #+#    #+#             */
/*   Updated: 2023/03/08 11:49:37 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "structs.h"
#include <math.h>

static void	set_col_display(t_cub3d *cube, t_float_vector player_pos, \
	t_ray *ray, int col);
static void	set_ray_parameters(t_ray *ray, t_float_vector player_pos);
static void	find_the_hit_wall(char **grid_maze, t_ray *ray, \
	int *is_a_wall_hit, int *is_wall_hit_on_x_axe);
static void	fill_col_display(t_cub3d *cube, t_ray *ray, \
	int is_wall_hit_on_x_axis, int col);

void	raytracer(t_cub3d *cube)
{
	int				y;
	float			relative_pos_in_screen;
	t_ray			ray;
	t_float_vector	p_dir;
	t_float_vector	p_pos;

	p_dir = cube->player.dir;
	p_pos = cube->player.pos;
	y = 0;
	while (y < WIN_W)
	{
		ray.direction.x = -p_dir.y;
		ray.direction.y = p_dir.x;
		ray.moving_direction.x = 1;
		ray.moving_direction.y = 1;
		relative_pos_in_screen = 2.0f * (float)y / (float)WIN_W - 1;
		ray.direction.x = ray.direction.x * relative_pos_in_screen + p_dir.x;
		ray.direction.y = ray.direction.y * relative_pos_in_screen + p_dir.y;
		set_col_display(cube, p_pos, &ray, y);
		y++;
	}
}

static void	set_col_display(t_cub3d *cube, t_float_vector player_pos, \
	t_ray *ray, int col)
{
	int			is_a_wall_hit;
	int			is_wall_hit_on_x_axis;

	ray->map_pos.x = (int)player_pos.x;
	ray->map_pos.y = (int)player_pos.y;
	set_ray_parameters(ray, player_pos);
	is_a_wall_hit = 0;
	find_the_hit_wall(cube->map_display.grid_maze, ray, &is_a_wall_hit, \
	&is_wall_hit_on_x_axis);
	fill_col_display(cube, ray, is_wall_hit_on_x_axis, col);
	if (cube->map_display.ray_texture[col] == 'N')
		cube->map_display.wall_pos_x[col] = (int)(ray->relative_hit_on_wall * (float)cube->map_display.north_texture_size.x);
	if (cube->map_display.ray_texture[col] == 'S')
		cube->map_display.wall_pos_x[col] = (int)(ray->relative_hit_on_wall * (float)cube->map_display.south_texture_size.x);
	if (cube->map_display.ray_texture[col] == 'W')
		cube->map_display.wall_pos_x[col] = (int)(ray->relative_hit_on_wall * (float)cube->map_display.west_texture_size.x);
	if (cube->map_display.ray_texture[col] == 'E')
		cube->map_display.wall_pos_x[col] = (int)(ray->relative_hit_on_wall * (float)cube->map_display.east_texture_size.x);
}

static void	set_ray_parameters(t_ray *ray, t_float_vector player_pos)
{
	ray->next_wall_hit.x = 1 / ray->direction.x;
	if (ray->direction.x < 0)
	{
		ray->next_wall_hit.x *= -1;
		ray->moving_direction.x = -1;
		ray->closest_side_wall.x = (player_pos.x - (float)ray->map_pos.x) \
		* ray->next_wall_hit.x;
	}
	else
		ray->closest_side_wall.x = ((float)ray->map_pos.x + 1.0f - player_pos.x) * \
		ray->next_wall_hit.x;
	ray->next_wall_hit.y = 1 / ray->direction.y;
	if (ray->direction.y < 0)
	{
		ray->next_wall_hit.y *= -1;
		ray->moving_direction.y = -1;
		ray->closest_side_wall.y = (player_pos.y - (float)ray->map_pos.y) * \
		ray->next_wall_hit.y;
	}
	else
		ray->closest_side_wall.y = ((float)ray->map_pos.y + 1.0f - player_pos.y) * \
		ray->next_wall_hit.y;
}

static void	find_the_hit_wall(char **grid_maze, t_ray *ray, \
	int *is_a_wall_hit, int *is_wall_hit_on_x_axe)
{
	t_float_vector	*next_wall_hit;
	t_float_vector	*closest_side_wall;
	t_int_vector	*map_pos;
	t_int_vector	*moving_direction;

	next_wall_hit = &ray->next_wall_hit;
	closest_side_wall = &ray->closest_side_wall;
	map_pos = &ray->map_pos;
	moving_direction = &ray->moving_direction;
	while (*is_a_wall_hit == 0)
	{
		if (closest_side_wall->x < closest_side_wall->y)
		{
			closest_side_wall->x += next_wall_hit->x;
			map_pos->x += moving_direction->x;
			*is_wall_hit_on_x_axe = 0;
		}
		else
		{
			closest_side_wall->y += next_wall_hit->y;
			map_pos->y += moving_direction->y;
			*is_wall_hit_on_x_axe = 1;
		}
		*is_a_wall_hit = (grid_maze[map_pos->y][map_pos->x] == '1');
	}
}

static void	fill_col_display(t_cub3d *cube, t_ray *ray, \
	int is_wall_hit_on_x_axis, int col)
{
	if (is_wall_hit_on_x_axis == 0)
	{
		cube->map_display.ray_size[col] = (int)(WIN_H / \
			(ray->closest_side_wall.x - ray->next_wall_hit.x));
		ray->relative_hit_on_wall = (ray->closest_side_wall.x - ray->next_wall_hit.x) * ray->direction.y + cube->player.pos.y;
		if (ray->moving_direction.x < 0)
			cube->map_display.ray_texture[col] = 'W';
		else
			cube->map_display.ray_texture[col] = 'E';
	}
	else
	{
		cube->map_display.ray_size[col] = (int)(WIN_H / \
			(ray->closest_side_wall.y - ray->next_wall_hit.y));
		ray->relative_hit_on_wall = (ray->closest_side_wall.y - ray->next_wall_hit.y) * ray->direction.x  + cube->player.pos.x;
		if (ray->moving_direction.y < 0)
			cube->map_display.ray_texture[col] = 'N';
		else
			cube->map_display.ray_texture[col] = 'S';
	}
	ray->relative_hit_on_wall -= roundf(ray->relative_hit_on_wall);
	if (ray->relative_hit_on_wall < 0)
			ray->relative_hit_on_wall *= -1;
}
