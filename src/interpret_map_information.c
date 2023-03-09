/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret_map_information.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 16:24:31 by jlitaudo          #+#    #+#             */
/*   Updated: 2023/03/09 10:28:30 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "errors.h"

static void	create_maze(t_cub3d *cube, char **map_information);
static void	fill_maze(t_cub3d *cube, char **grid_maze, char **map_information);

void	interpret_map_information(t_cub3d *cube, char **map_info)
{
	int	i;

	i = 0;
	while (i < 6)
	{
		if (!map_info[i])
			error_exit_cube(cube, INVALID_PATTERN, "");
		find_texture_path_and_get_color(cube, map_info[i]);
		i++;
	}
	if (!map_info[i])
		error_exit_cube(cube, INVALID_PATTERN, "");
	create_maze(cube, &map_info[i]);
	fill_maze(cube, cube->display.grid_maze, &map_info[i]);
	maze_validity_checking(cube, cube->display.grid_maze);
}

static void	create_maze(t_cub3d *cube, char **map_information)
{
	int		i;
	size_t	len;
	size_t	len_max;

	len_max = ft_strlen(map_information[0]);
	i = -1;
	while (map_information[++i])
	{
		len = ft_strlen(map_information[i]);
		if (len > len_max)
			len_max = len;
	}
	cube->display.grid_maze = malloc(sizeof(char *) * (i + 1));
	cube->display.maze_size.y = i;
	cube->display.maze_size.x = (int) len_max;
	test_failed_malloc(cube, cube->display.grid_maze);
	cube->display.grid_maze[i] = NULL;
	i = -1;
	while (map_information[++i])
	{
		cube->display.grid_maze[i] = malloc(sizeof(char) * (len_max + 1));
		test_failed_malloc(cube, cube->display.grid_maze[i]);
		ft_memset(cube->display.grid_maze[i], ' ', len_max);
		cube->display.grid_maze[i][len_max] = 0;
	}
}

static void	fill_maze(t_cub3d *cube, char **grid_maze, char **map_information)
{
	int		line;
	int		i;

	line = 0;
	while (map_information[line])
	{
		i = -1;
		while (map_information[line][++i])
		{
			if (ft_is_inside(map_information[line][i], GRID_CHARSET) == 0)
				error_exit_cube(cube, INVALID_MAZE_CHAR, map_information[line]);
			grid_maze[line][i] = map_information[line][i];
		}
		line++;
	}
}
