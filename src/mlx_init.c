/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 13:42:41 by cpalusze          #+#    #+#             */
/*   Updated: 2023/03/08 12:02:06 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

enum e_result	init_mlx_data(t_mlx_data *mlx_data)
{
	mlx_data->mlx_win = NULL;
	mlx_data->mlx_img.img = NULL;
	mlx_data->mlx = mlx_init();
	if (mlx_data->mlx == NULL)
		return (ERROR);
	mlx_data->mlx_win = mlx_new_window(mlx_data->mlx, WIN_W, WIN_H, WIN_NAME);
	if (mlx_data->mlx_win == NULL)
		return (ERROR);
	mlx_data->mlx_img.img = mlx_new_image(mlx_data->mlx, WIN_W, WIN_H);
	if (mlx_data->mlx_img.img == NULL)
		return (ERROR);
	mlx_data->mlx_img.addr = mlx_get_data_addr(mlx_data->mlx_img.img, \
									&mlx_data->mlx_img.bits_per_pixel, \
							&mlx_data->mlx_img.line_length, \
								&mlx_data->mlx_img.endian);
	if (mlx_data->mlx_img.addr == NULL)
		return (ERROR);
	return (SUCCESS);
}
