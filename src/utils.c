/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlitaudo <jlitaudo@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 09:57:28 by cpalusze          #+#    #+#             */
/*   Updated: 2023/02/28 16:55:23 by jlitaudo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	test_failed_malloc(t_cub3d *cube, void *content)
{
	if (!content)
		error_exit_cube(cube, ERR_MALLOC, "");
}

void	error_exit_cube(t_cub3d *cube, char *msg1, char *msg2)
{
	ft_printf_fd(2, "Error\n");
	ft_printf_fd(2, "%s: %s\n", msg1, msg2);
	exit_cube(cube, EXIT_FAILURE);
}

void	exit_cube(t_cub3d *cube, int exit_code)
{
	(void) cube;
	printf("Exit\n");
	ft_free_split(cube->map_information);
	ft_free_split(cube->grid_maze);
	ft_free(cube->map_display.north_texture);
	ft_free(cube->map_display.south_texture);
	ft_free(cube->map_display.east_texture);
	ft_free(cube->map_display.west_texture);

	exit(exit_code);
}