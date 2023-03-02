/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlitaudo <jlitaudo@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 14:28:20 by cpalusze          #+#    #+#             */
/*   Updated: 2023/03/02 11:09:21 by jlitaudo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

// Todo: why int function ?
int	game_loop(t_cub3d *cube)
{
	int render_needed;

	render_needed = 0;
	if (cube->player.move.y != 0)
	{
		// Move player
		cube->player.pos.x += 0.1f * cube->player.dir.x * cube->player.move.y;
		cube->player.pos.y += 0.1f * cube->player.dir.y * cube->player.move.y;
		render_needed = 1;
	}
	if (cube->player.move.x != 0)
	{
		// Move player
		cube->player.pos.x += - 0.1f * cube->player.dir.y * cube->player.move.x;
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