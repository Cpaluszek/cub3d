/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 14:28:20 by cpalusze          #+#    #+#             */
/*   Updated: 2023/03/01 14:38:51 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Todo: why int function ?
int	game_loop(t_cub3d *cube)
{
	int render_needed;

	render_needed = 0;
	if (cube->player.move.x != 0 || cube->player.move.y != 0)
	{
		// Move player
		render_needed = 1;
	}
	if (cube->player.rotate != 0)
	{
		// Rotate player
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