/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 14:28:20 by cpalusze          #+#    #+#             */
/*   Updated: 2023/03/09 14:29:56 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

static int	move_player_x(t_cub3d *cube);
static int	move_player_y(t_cub3d *cube);
static int	rotate_player(t_cub3d *cube);

int	game_loop(t_cub3d *cube)
{
	static int	last_player_attack_state;
	int			render_needed;

	render_needed = 0;
	if (cube->player.move.y != 0)
		render_needed = move_player_y(cube);
	if (cube->player.move.x != 0)
		render_needed = move_player_x(cube);
	if (cube->player.rotate != 0)
		render_needed = rotate_player(cube);
	if (cube->player.attack_state != last_player_attack_state)
	{
		last_player_attack_state = cube->player.attack_state;
		render_needed = 1;
	}
	if (render_needed == 1)
		render(cube);
	return (0);
}

static int	rotate_player(t_cub3d *cube)
{
	cube->player.angle += cube->player.rotate;
	cube->player.dir.x = cosf(cube->player.angle);
	cube->player.dir.y = sinf(cube->player.angle);
	return (1);
}

static int	move_player_x(t_cub3d *cube)
{
	int		wall;
	float	dx;
	float	dy;

	wall = (int)(cube->player.pos.x + -SCREEN_DIST * \
		cube->player.dir.y * cube->player.move.x);
	if (ft_is_inside(cube->display.grid_maze[(int)cube->player.pos.y][wall], \
		NO_COLLISION_CHARSET))
	{
		dx = -SCREEN_DIST * cube->player.dir.y * cube->player.move.x;
		cube->player.pos.x += dx;
	}
	wall = (int)(cube->player.pos.y + SCREEN_DIST * \
		cube->player.dir.x * cube->player.move.x);
	if (ft_is_inside(cube->display.grid_maze[wall][(int)cube->player.pos.x], \
		NO_COLLISION_CHARSET))
	{
		dy = SCREEN_DIST * cube->player.dir.x * cube->player.move.x;
		cube->player.pos.y += dy;
	}
	return (1);
}

static int	move_player_y(t_cub3d *cube)
{
	int		wall;
	float	dx;
	float	dy;

	wall = (int)(cube->player.pos.x + SCREEN_DIST * \
		cube->player.dir.x * cube->player.move.y);
	if (ft_is_inside(cube->display.grid_maze[(int)cube->player.pos.y][wall], \
		NO_COLLISION_CHARSET))
	{
		dx = SCREEN_DIST * cube->player.dir.x * cube->player.move.y;
		cube->player.pos.x += dx;
	}
	wall = (int)(cube->player.pos.y + SCREEN_DIST * \
		cube->player.dir.y * cube->player.move.y);
	if (ft_is_inside(cube->display.grid_maze[wall][(int)cube->player.pos.x], \
		NO_COLLISION_CHARSET))
	{
		dy = SCREEN_DIST * cube->player.dir.y * cube->player.move.y;
		cube->player.pos.y += dy;
	}
	return (1);
}
