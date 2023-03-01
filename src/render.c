/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 09:50:14 by cpalusze          #+#    #+#             */
/*   Updated: 2023/03/01 10:28:58 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_minimap(t_cub3d *cube);

void	init_render(t_cub3d *cube)
{
	cube->mlx_data.working_img = &cube->mlx_data.img1;
	draw_minimap(cube);
}

