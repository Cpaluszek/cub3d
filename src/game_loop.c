/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 14:28:20 by cpalusze          #+#    #+#             */
/*   Updated: 2023/03/04 11:25:15 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

static void	move_player_x(t_cub3d *cube);
static void	move_player_y(t_cub3d *cube);

int	game_loop(t_cub3d *cube)
{
	int	render_needed;

	render_needed = 0;
	if (cube->player.move.y != 0)
	{
		move_player_y(cube);
		render_needed = 1;
	}
	if (cube->player.move.x != 0)
	{
		move_player_x(cube);
		render_needed = 1;
	}
	if (cube->player.rotate != 0)
	{
		cube->player.angle += cube->player.rotate;
		cube->player.dir.x = cos(cube->player.angle);
		cube->player.dir.y = sin(cube->player.angle);
		render_needed = 1;
	}
	if (render_needed == 1)
		init_render(cube);
	return (0);
}

static void	move_player_x(t_cub3d *cube)
{
	int		wall;
	float	dx;
	float	dy;

	wall = (int)(cube->player.pos.x + -SCREEN_DIST * \
		cube->player.dir.y * cube->player.move.x);
	if (cube->map_display.grid_maze[(int)cube->player.pos.y][wall] == '0')
	{
		dx = -SCREEN_DIST * cube->player.dir.y * cube->player.move.x;
		cube->player.pos.x += dx;
	}
	wall = (int)(cube->player.pos.y + SCREEN_DIST * \
		cube->player.dir.x * cube->player.move.x);
	if (cube->map_display.grid_maze[wall][(int)cube->player.pos.x] == '0')
	{
		dy = SCREEN_DIST * cube->player.dir.x * cube->player.move.x;
		cube->player.pos.y += dy;
	}
}

static void	move_player_y(t_cub3d *cube)
{
	int		wall;
	float	dx;
	float	dy;

	wall = (int)(cube->player.pos.x + SCREEN_DIST * \
		cube->player.dir.x * cube->player.move.y);
	if (cube->map_display.grid_maze[(int)cube->player.pos.y][wall] == '0')
	{
		dx = SCREEN_DIST * cube->player.dir.x * cube->player.move.y;
		cube->player.pos.x += dx;
	}
	wall = (int)(cube->player.pos.y + SCREEN_DIST * \
		cube->player.dir.y * cube->player.move.y);
	if (cube->map_display.grid_maze[wall][(int)cube->player.pos.x] == '0')
	{
		dy = SCREEN_DIST * cube->player.dir.y * cube->player.move.y;
		cube->player.pos.y += dy;
	}
}
