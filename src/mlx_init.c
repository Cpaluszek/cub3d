/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 13:42:41 by cpalusze          #+#    #+#             */
/*   Updated: 2023/02/28 13:51:52 by cpalusze         ###   ########.fr       */
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
	return (SUCCESS);
}


int   printkey(int key)
{
    return (printf("%d\n", key));
}

void	set_mlx_hooks(t_mlx_data *mlx_data)
{
	mlx_key_hook(mlx_data->mlx_win, printkey, NULL);
}