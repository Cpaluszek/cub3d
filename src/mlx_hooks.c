/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlitaudo <jlitaudo@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 15:21:37 by cpalusze          #+#    #+#             */
/*   Updated: 2023/03/02 14:27:32 by jlitaudo         ###   ########.fr       */
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
	mlx_hook(cube->mlx_data.mlx_win, ON_KEYDOWN, 0x1, key_press_hook, cube);
	mlx_hook(cube->mlx_data.mlx_win, ON_KEYUP, 0x2, key_release_hook, cube);
	mlx_hook(cube->mlx_data.mlx_win, ON_BUTTON_PRESS, 1L << 0, button_hook, cube);
	mlx_hook(cube->mlx_data.mlx_win, 6, 1L << 6, camera_on_mouse, cube);
}

// Todo: test multiple key hooks
static int   key_press_hook(int key, t_cub3d *cube)
{
	dprintf(2, "Key press %d\n", key);
	if (key == ESC)
		exit_cube(cube, SUCCESS);
	// Directions
	else if (key == KEY_W)
		cube->player.move.y = 1;
	else if (key == KEY_S)
		cube->player.move.y = -1;
	else if (key == KEY_A)
		cube->player.move.x = -1;
	else if (key == KEY_D)
		cube->player.move.x = 1;
	// Rotations
	else if (key == KEY_Q || key == ARROW_LEFT)
		cube->player.rotate = -PI * 0.01;
	else if (key == KEY_E || key == ARROW_RIGHT)
		cube->player.rotate = PI * 0.01;
	else
		printf("%d\n", key);
	return (0);
}

static int key_release_hook(int key, t_cub3d *cube)
{
	// Directions
//	dprintf(2, "Key release %d\n", key);
	if (key == KEY_W || key == KEY_S)
		cube->player.move.y = 0;
	else if (key == KEY_A || key == KEY_D)
		cube->player.move.x = 0;
	// Rotations
	else if (key == KEY_Q || key == ARROW_LEFT || key == KEY_E || key == ARROW_RIGHT)
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
	float distance_from_screen_side;

	(void)y;
	if (cube->player.move.x || cube->player.move.y)
	{
		distance_from_screen_side = ((float)(WIN_WIDTH / 2) - x) / WIN_WIDTH;
		dprintf(2, "ANGLE BEFORE  %f\n", cube->player.angle);
		cube->player.angle += PI / 50 * -distance_from_screen_side;
		dprintf(2, "ANGLE AFTER  %f\n", cube->player.angle);
		cube->player.dir.x = cos(cube->player.angle);
		cube->player.dir.y = sin(cube->player.angle);
	}
	return (0);
}