/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_mouse_hooks.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 15:04:58 by cpalusze          #+#    #+#             */
/*   Updated: 2023/03/08 15:06:34 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

int	mouse_down_hook(int button, int x, int y, t_cub3d *cube)
{
	(void) x;
	(void) y;
	if (button != MOUSE_LEFT)
		return (0);
	cube->player.attack_state = 1;
	return (0);
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
