/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_texture_array.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 17:00:25 by jlitaudo          #+#    #+#             */
/*   Updated: 2023/03/08 11:31:54 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "structs.h"
#include "errors.h"

static int	**load_texture(t_cub3d *cube, void *mlx, char *texture_path, t_int_vector *size);

void	create_texture_array(t_cub3d *cube)
{
	void	*mlx_ptr;

	mlx_ptr = cube->mlx_data.mlx;
	cube->map_display.north_texture = load_texture(cube, mlx_ptr, cube->textures_paths.north_texture_path, &cube->map_display.north_texture_size);
	cube->map_display.south_texture = load_texture(cube, mlx_ptr, cube->textures_paths.south_texture_path, &cube->map_display.south_texture_size);
	cube->map_display.west_texture = load_texture(cube, mlx_ptr, cube->textures_paths.west_texture_path, &cube->map_display.west_texture_size);
	cube->map_display.east_texture = load_texture(cube, mlx_ptr, cube->textures_paths.east_texture_path, &cube->map_display.east_texture_size);
//	dprintf(1, "%d %d %d %d\n", cube->map_display.east_texture_size.x, cube->map_display.east_texture_size.x, cube->map_display.east_texture_size.x, cube->map_display.east_texture_size.x);
}

static int	**load_texture(t_cub3d *cube, void *mlx, char *texture_path, t_int_vector *size)
{
	t_texture		texture;
	int	**texture_array;
	int 			i;

//	dprintf(1, "%s\n", texture_path);
	texture.address = mlx_xpm_file_to_image(mlx, texture_path, &texture.width, &texture.height);
	if (texture.address == NULL) // Todo: Check conversion error
		error_exit_cube(cube, ERR_MLX_XPM, ERR_XPM_CONV);
	texture.text = mlx_get_data_addr(texture.address, &texture.bits_per_pixel, &texture.line_length, &texture.endian);
	if (texture.text == NULL)
		error_exit_cube(cube, ERR_MLX_XPM, ERR_XPM_ADDR);
	texture_array = malloc(sizeof(unsigned int *) * (texture.height));
	test_failed_malloc(cube, texture_array);
	i = 0;
	while (i < texture.width)
	{
		texture_array[i] = malloc(sizeof(int) * (texture.width));
		test_failed_malloc(cube, texture_array[i]);
		i++;
	}

	int x;
	i = 0;
	while (i < texture.height)
	{
		x = 0;
		while (x < texture.width)
		{
			texture_array[i][x] = *(int *)(texture.text + (i * texture.line_length + x * (texture.bits_per_pixel / 8)));
//			dprintf(1, "%x ", texture_array[i][x]);
			x++;
		}
//		dprintf(1, "\n");
		i++;
	}
	size->x = texture.width;
	size->y = texture.height;
	mlx_destroy_image(mlx, texture.address);
	return (texture_array);
}