/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_texture_array.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 17:00:25 by jlitaudo          #+#    #+#             */
/*   Updated: 2023/03/08 14:56:26 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "structs.h"
#include "errors.h"

static int	**load_texture(t_cub3d *cube, void *mlx, \
	char *path, t_int_vector *size);
static int	**fill_texture_content(t_cub3d *cube, t_mlx_texture texture);

void	create_texture_array(t_cub3d *cube)
{
	void	*mlx_ptr;

	mlx_ptr = cube->mlx_data.mlx;
	cube->display.north_tex.content = load_texture(cube, mlx_ptr, \
		cube->textures_paths.north_texture_path, &cube->display.north_tex.size);
	cube->display.south_tex.content = load_texture(cube, mlx_ptr, \
		cube->textures_paths.south_texture_path, &cube->display.south_tex.size);
	cube->display.west_tex.content = load_texture(cube, mlx_ptr, \
		cube->textures_paths.west_texture_path, &cube->display.west_tex.size);
	cube->display.east_tex.content = load_texture(cube, mlx_ptr, \
		cube->textures_paths.east_texture_path, &cube->display.east_tex.size);
	cube->display.torch_attack_tex.content = load_texture(cube, mlx_ptr, \
		TORCH_ATTACK_TEX_PATH, &cube->display.torch_attack_tex.size);
	cube->display.torch_idle_tex.content = load_texture(cube, mlx_ptr, \
		TORCH_IDLE_TEX_PATH, &cube->display.torch_idle_tex.size);
}

static int	**load_texture(t_cub3d *cube, void *mlx, char *path, \
	t_int_vector *size)
{
	t_mlx_texture	texture;
	int				**texture_array;

	texture.address = mlx_xpm_file_to_image(mlx, path, \
		&texture.width, &texture.height);
	if (texture.address == NULL)
		error_exit_cube(cube, ERR_MLX_XPM, ERR_XPM_CONV);
	texture.text = mlx_get_data_addr(texture.address, &texture.bits_per_pixel, \
		&texture.line_length, &texture.endian);
	if (texture.text == NULL)
		error_exit_cube(cube, ERR_MLX_XPM, ERR_XPM_ADDR);
	texture_array = fill_texture_content(cube, texture);
	size->x = texture.width;
	size->y = texture.height;
	mlx_destroy_image(mlx, texture.address);
	return (texture_array);
}

static int	**fill_texture_content(t_cub3d *cube, t_mlx_texture texture)
{
	int	**texture_array;
	int	y;
	int	x;

	texture_array = malloc(sizeof(unsigned int *) * (texture.height));
	test_failed_malloc(cube, texture_array);
	y = -1;
	while (++y < texture.width)
	{
		texture_array[y] = malloc(sizeof(int) * (texture.width));
		test_failed_malloc(cube, texture_array[y]);
	}
	y = 0;
	while (y < texture.height)
	{
		x = 0;
		while (x < texture.width)
		{
			texture_array[y][x] = *(int *)(texture.text + \
				(y * texture.line_length + x * (texture.bits_per_pixel / 8)));
			x++;
		}
		y++;
	}
	return (texture_array);
}
