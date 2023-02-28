/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 15:21:37 by cpalusze          #+#    #+#             */
/*   Updated: 2023/02/28 15:37:31 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	button_hook(t_cub3d *cube);

int   key_press_hook(int key, t_cub3d *cube)
{
	(void) cube;
	if (key == ESC)
		exit_cube(cube, SUCCESS);
	else
		printf("%d\n", key);
	return (0);
}

void	set_mlx_hooks(t_cub3d *cube)
{
	mlx_hook(cube->mlx_data.mlx_win, ON_KEYDOWN, 1L << 0, key_press_hook, cube);
//	mlx_hook(cube->mlx_data.mlx_win, ON_KEYUP, 1L << 0, key_release_hook, cube);
	mlx_hook(cube->mlx_data.mlx_win, ON_BUTTON_PRESS, 1L << 0, button_hook, cube);
}

static int	button_hook(t_cub3d *cube)
{
	(void) cube;
	exit_cube(cube, SUCCESS);
	return (0);
}