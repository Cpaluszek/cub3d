/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 13:42:41 by cpalusze          #+#    #+#             */
/*   Updated: 2023/02/28 15:26:34 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

enum e_result	init_mlx_data(t_mlx_data *mlx_data)
{
	mlx_data->mlx = mlx_init();
	if (mlx_data->mlx == NULL)
		return (ERROR);
	mlx_data->mlx_win = mlx_new_window(mlx_data->mlx, WIN_WIDTH, WIN_HEIGHT, WIN_NAME);
	if (mlx_data->mlx_win == NULL)
	{
		// Todo: destroy mlx ??
		return (ERROR);
	}
	mlx_data->img1.img = mlx_new_image(mlx_data->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (mlx_data->img1.img == NULL)
	{
		// Todo: clean exit
		return (ERROR);
	}
	mlx_data->img1.addr = mlx_get_data_addr(mlx_data->img1.img, &mlx_data->img1.bits_per_pixel,
											&mlx_data->img1.line_length, &mlx_data->img1.endian);
	if (mlx_data->img1.addr == NULL)
	{
		// Todo: clean exit
		return (ERROR);
	}
	return (SUCCESS);
}
