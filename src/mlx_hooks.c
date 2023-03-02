/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 15:21:37 by cpalusze          #+#    #+#             */
/*   Updated: 2023/03/02 10:18:40 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	button_hook(t_cub3d *cube);
static int	key_press_hook(int key, t_cub3d *cube);
static int	key_release_hook(int key, t_cub3d *cube);

void	set_mlx_hooks(t_cub3d *cube)
{
	mlx_hook(cube->mlx_data.mlx_win, ON_KEYDOWN, 1L << 0, key_press_hook, cube);
	mlx_hook(cube->mlx_data.mlx_win, ON_KEYUP, 1L << 1, key_release_hook, cube);
	mlx_hook(cube->mlx_data.mlx_win, ON_BUTTON_PRESS, 1L << 0, button_hook, cube);
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
		cube->player.move.x = 1;
	else if (key == KEY_D)
		cube->player.move.x = -1;
	// Rotations
	else if (key == KEY_Q || key == ARROW_LEFT)
		cube->player.rotate = -1;
	else if (key == KEY_E || key == ARROW_RIGHT)
		cube->player.rotate = 1;
	else
		printf("%d\n", key);
	return (0);
}

static int key_release_hook(int key, t_cub3d *cube)
{
	// Directions
	dprintf(2, "Key release %d\n", key);
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
