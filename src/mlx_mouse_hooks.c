/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_mouse_hooks.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 15:04:58 by cpalusze          #+#    #+#             */
/*   Updated: 2023/03/09 12:56:02 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

static void	check_nearby_door(t_cub3d *cube, int x, int y);

int	mouse_down_hook(int button, int x, int y, t_cub3d *cube)
{
	int dx;
	int dy;

	if (button != MOUSE_LEFT)
		return (0);
	x = (int)roundf(cube->player.pos.x + cube->player.dir.x);
	y = (int)roundf(cube->player.pos.y + cube->player.dir.y);
	dx = (int)cube->player.pos.x - x;
	dy = (int)cube->player.pos.y - y;
	check_nearby_door(cube, x, y);
	if (dx != 0)
	{
		check_nearby_door(cube, x + 1, y);
		check_nearby_door(cube, x - 1, y);
	}
	if (dy != 0)
	{
		check_nearby_door(cube, x, y + 1)	;
		check_nearby_door(cube, x, y - 1);
	}
	cube->player.attack_state = 1;
	return (0);
}

static void	check_nearby_door(t_cub3d *cube, int x, int y)
{
	if (x < 0 || y < 0)
		return ;
	if (x >= cube->display.maze_size.x || y >= cube->display.maze_size.y)
		return ;
	if (cube->display.grid_maze[y][x] == CLOSED_DOOR_CHAR)
		cube->display.grid_maze[y][x] = OPEN_DOOR_CHAR;
	else if (cube->display.grid_maze[y][x] == OPEN_DOOR_CHAR)
		cube->display.grid_maze[y][x] = CLOSED_DOOR_CHAR;
}

int	mouse_up_hook(int button, int x, int y, t_cub3d *cube)
{
	(void) x;
	(void) y;
	if (button != MOUSE_LEFT)
		return (0);
	cube->player.attack_state = 0;
	return (0);
}

int	mouse_move_hook(int x, int y, t_cub3d *cube)
{
	float	distance_from_screen_side;

	(void)y;
	if (!cube->player.move.x && !cube->player.move.y)
		return (0);
	distance_from_screen_side = ((float)(WIN_W / 2) - x) / WIN_W;
	cube->player.angle += MOUSE_ROT_SPEED * -distance_from_screen_side;
	cube->player.dir.x = cosf(cube->player.angle);
	cube->player.dir.y = sinf(cube->player.angle);
	return (0);
}
