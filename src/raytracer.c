/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlitaudo <jlitaudo@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 11:27:24 by jlitaudo          #+#    #+#             */
/*   Updated: 2023/03/03 15:30:41 by jlitaudo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "structs.h"

static void	set_col_display(t_cub3d *cube, t_float_vector player_pos, \
	t_ray ray, int col);
static void	set_ray_parameters(t_ray *ray, t_float_vector player_pos);
static void	find_the_hit_wall(char **grid_maze, t_ray *ray, int *is_a_wall_hit, int *is_wall_hit_on_x_axe);

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
		relative_pos_in_screen = 2 * y / (double)WIN_W - 1;
		ray.direction.x = ray.direction.x * relative_pos_in_screen + p_dir.x;
		ray.direction.y = ray.direction.y * relative_pos_in_screen + p_dir.y;
		set_col_display(cube, p_pos, ray, y);
		y++;
	}
}

static void	set_col_display(t_cub3d *cube, t_float_vector player_pos, \
	t_ray ray, int col)
{
	int			is_a_wall_hit;
	int			is_wall_hit_on_x_axe;

	ray.map_pos.x = (int)player_pos.x;
	ray.map_pos.y = (int)player_pos.y;
	set_ray_parameters(&ray, player_pos);
	is_a_wall_hit = 0;
	find_the_hit_wall(cube->map_display.grid_maze, &ray, &is_a_wall_hit, &is_wall_hit_on_x_axe);
	if (is_wall_hit_on_x_axe == 0)
	{
		cube->map_display.raysize[col] = (int)(WIN_H / (ray.closest_side_wall.x - ray.next_wall_hit.x));
		if (ray.moving_direction.x < 0)
			cube->map_display.raytexture[col] = 'W';
		else
			cube->map_display.raytexture[col] = 'E';
	}
	else
	{
		cube->map_display.raysize[col] = (int)(WIN_H / (ray.closest_side_wall.y - ray.next_wall_hit.y));
		if (ray.moving_direction.y < 0)
			cube->map_display.raytexture[col] = 'N';
		else
			cube->map_display.raytexture[col] = 'S';
	}
}

static void	set_ray_parameters(t_ray *ray, t_float_vector player_pos)
{
	if (ray->direction.x < 0)
	{
		ray->next_wall_hit.x = -1 * (1 / ray->direction.x);
		ray->moving_direction.x = -1;
		ray->closest_side_wall.x = (player_pos.x - ray->map_pos.x) * ray->next_wall_hit.x;
	}
	else
	{
		ray->next_wall_hit.x = 1 / ray->direction.x;
		ray->moving_direction.x = 1;
		ray->closest_side_wall.x = (ray->map_pos.x + 1.0f - player_pos.x) * ray->next_wall_hit.x;
	}
	if (ray->direction.y < 0)
	{
		ray->next_wall_hit.y = -1 * (1 / ray->direction.y);
		ray->moving_direction.y = -1;
		ray->closest_side_wall.y = (player_pos.y - ray->map_pos.y) * ray->next_wall_hit.y;
	}
	else
	{
		ray->next_wall_hit.y = 1 / ray->direction.y;
		ray->moving_direction.y = 1;
		ray->closest_side_wall.y = (ray->map_pos.y + 1.0f - player_pos.y) * ray->next_wall_hit.y;
	}
}

static void	find_the_hit_wall(char **grid_maze, t_ray *ray, int *is_a_wall_hit, int *is_wall_hit_on_x_axe)
{
	t_float_vector	*next_wall_hit;
	t_float_vector	*closest_side_wall;
	t_int_vector 	*map_pos;
	t_int_vector 	*moving_direction;

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
		} else
		{
			closest_side_wall->y += next_wall_hit->y;
			map_pos->y += moving_direction->y;
			*is_wall_hit_on_x_axe = 1;
		}
		if (grid_maze[map_pos->y][map_pos->x] == '1')
			*is_a_wall_hit = 1;
	}
}