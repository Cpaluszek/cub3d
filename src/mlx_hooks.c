/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 15:21:37 by cpalusze          #+#    #+#             */
/*   Updated: 2023/03/02 15:25:06 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

static int	button_hook(t_cub3d *cube);
static int	key_press_hook(int key, t_cub3d *cube);
static int	key_release_hook(int key, t_cub3d *cube);
static int	camera_on_mouse(int x, int y, t_cub3d *cube);

void	set_mlx_hooks(t_cub3d *cube)
{
	void	*win_ptr;

	win_ptr = cube->mlx_data.mlx_win;
	mlx_hook(win_ptr, ON_KEYDOWN, 1L << 0, key_press_hook, cube);
	mlx_hook(win_ptr, ON_KEYUP, 1L << 1, key_release_hook, cube);
	mlx_hook(win_ptr, ON_BUTTON_PRESS, 1L << 0, button_hook, cube);
	mlx_hook(win_ptr, 6, 1L << 6, camera_on_mouse, cube);
}

static int	key_press_hook(int key, t_cub3d *cube)
{
	dprintf(2, "Key press %d\n", key);
	if (key == ESC)
		exit_cube(cube, SUCCESS);
	else if (key == KEY_W)
		cube->player.move.y = 1;
	else if (key == KEY_S)
		cube->player.move.y = -1;
	else if (key == KEY_A)
		cube->player.move.x = -1;
	else if (key == KEY_D)
		cube->player.move.x = 1;
	else if (key == KEY_Q || key == ARROW_LEFT)
		cube->player.rotate = -PI * 0.01f;
	else if (key == KEY_E || key == ARROW_RIGHT)
		cube->player.rotate = PI * 0.01f;
	return (0);
}

static int	key_release_hook(int key, t_cub3d *cube)
{
	if (key == KEY_W || key == KEY_S)
		cube->player.move.y = 0;
	else if (key == KEY_A || key == KEY_D)
		cube->player.move.x = 0;
	else if (key == KEY_Q || key == ARROW_LEFT || \
		key == KEY_E || key == ARROW_RIGHT)
		cube->player.rotate = 0;
	return (0);
}

static int	button_hook(t_cub3d *cube)
{
	exit_cube(cube, SUCCESS);
	return (0);
}

static int	camera_on_mouse(int x, int y, t_cub3d *cube)
{
	float	distance_from_screen_side;

	(void)y;
	if (cube->player.move.x || cube->player.move.y)
	{
		distance_from_screen_side = ((float)(WIN_W / 2) - x) / WIN_W;
		dprintf(2, "ANGLE BEFORE  %f\n", cube->player.angle);
		cube->player.angle += PI / 50 * -distance_from_screen_side;
		dprintf(2, "ANGLE AFTER  %f\n", cube->player.angle);
		cube->player.dir.x = cos(cube->player.angle);
		cube->player.dir.y = sin(cube->player.angle);
	}
	return (0);
}
