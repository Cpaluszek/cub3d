/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlitaudo <jlitaudo@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 14:28:20 by cpalusze          #+#    #+#             */
/*   Updated: 2023/03/02 14:26:39 by jlitaudo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

// Todo: why int function ?
int	game_loop(t_cub3d *cube)
{
	int render_needed;
	int is_a_wall;

	render_needed = 0;
	if (cube->player.move.y != 0)
	{
		is_a_wall = (int) (cube->player.pos.x + 0.1f * cube->player.dir.x * cube->player.move.y);
		if (cube->grid_maze[(int)cube->player.pos.y][is_a_wall] == '0')
			cube->player.pos.x += 0.1f * cube->player.dir.x * cube->player.move.y;
		is_a_wall = (int) (cube->player.pos.y + 0.1f * cube->player.dir.y * cube->player.move.y);
		if (cube->grid_maze[is_a_wall][(int)cube->player.pos.x] == '0')
			cube->player.pos.y += 0.1f * cube->player.dir.y * cube->player.move.y;
		render_needed = 1;
	}
	if (cube->player.move.x != 0)
	{
		is_a_wall = (int) (cube->player.pos.x + - 0.1f * cube->player.dir.y * cube->player.move.x);
		if (cube->grid_maze[(int)cube->player.pos.y][is_a_wall] == '0')
			cube->player.pos.x += - 0.1f * cube->player.dir.y * cube->player.move.x;
		is_a_wall = (int) (cube->player.pos.y + 0.1f * cube->player.dir.x * cube->player.move.x);
		if (cube->grid_maze[is_a_wall][(int)cube->player.pos.x] == '0')
			cube->player.pos.y += 0.1f * cube->player.dir.x * cube->player.move.x;
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
	{

		dprintf(2, "# ");
		init_render(cube);
	}
	render_needed = 0;
	return (0);
}
