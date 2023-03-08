/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_torch.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 13:16:26 by cpalusze          #+#    #+#             */
/*   Updated: 2023/03/08 14:27:23 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define TORCH_POS_X 1100
#define TORCH_POS_Y	830
#define TORCH_BG_COLOR 0x000000
#define SCALE 4

static t_int_vector	get_texture_size(t_cub3d *cube);
static int			**get_texture_content(t_cub3d *cube);

void	draw_torch(t_cub3d *cube)
{
	t_mlx_data		data;
	t_int_vector	pos;
	t_int_vector	texture_size;
	int				pixel_color;
	int				**texture_content;

	data = cube->mlx_data;
	texture_size = get_texture_size(cube);
	texture_content = get_texture_content(cube);
	pos.y = -1;
	while (++pos.y < texture_size.y * SCALE)
	{
		pos.x = -1;
		while (++pos.x < texture_size.x * SCALE)
		{
			pixel_color = texture_content[pos.y / SCALE][pos.x / SCALE];
			if (pixel_color != TORCH_BG_COLOR)
				my_mlx_pixel_put(&data.mlx_img, pos.x + TORCH_POS_X, \
					pos.y + TORCH_POS_Y, pixel_color);
		}
	}
}

static t_int_vector	get_texture_size(t_cub3d *cube)
{
	if (cube->player.attack_state == 1)
		return (cube->display.torch_attack_texture_size);
	return (cube->display.torch_idle_texture_size);
}

static int	**get_texture_content(t_cub3d *cube)
{
	if (cube->player.attack_state == 1)
		return (cube->display.torch_attack_texture);
	return (cube->display.torch_idle_texture);
}
