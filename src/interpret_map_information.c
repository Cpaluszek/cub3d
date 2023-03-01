/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret_map_information.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlitaudo <jlitaudo@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 16:24:31 by jlitaudo          #+#    #+#             */
/*   Updated: 2023/02/28 16:25:34 by jlitaudo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	create_maze(t_cub3d *cube, char **map_information);
static void	fill_maze(t_cub3d *cube, char **grid_maze, char **map_information);

void	interpret_map_information(t_cub3d *cube, char **map_information)
{
	int	i;

	i = 0;
	while (i < 6)
	{
		if (!map_information[i])
			error_exit_cube(cube, INVALID_PATTERN, "");
		find_texture_path_and_get_color(cube, map_information[i]);
		i++;
	}
	if (!map_information[i])
		error_exit_cube(cube, INVALID_PATTERN, "");
	create_maze(cube, &map_information[i]);
	fill_maze(cube, cube->grid_maze, &map_information[i]);
	maze_validity_checking(cube, cube->grid_maze);
}

void print_maze(char **maze)
{
	printf("--- Maze Content ---\n");
	for (int i = 0; maze[i]; i++)
	{
		printf("%s - %lu\n", maze[i], ft_strlen(maze[i]));
	}
	printf("--------------------\n");
}

static void	create_maze(t_cub3d *cube, char **map_information)
{
	int		i;
	size_t	len;
	size_t	len_max;

	len_max = ft_strlen(map_information[0]);
	i = 0;
	while (map_information[i])
	{
		len = ft_strlen(map_information[i]);
		if (len > len_max)
			len_max = len;
		i++;
	}
	cube->grid_maze = malloc(sizeof(char *) * (i + 1));
	test_failed_malloc(cube, cube->grid_maze);
	cube->grid_maze[i] = NULL;
	i = 0;
	while (map_information[i])
	{
		cube->grid_maze[i] = malloc(sizeof(char) * (len_max + 1));
		test_failed_malloc(cube, cube->grid_maze[i]);
		ft_memset(cube->grid_maze[i], ' ', len_max);
		i++;
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
			if (ft_is_inside(map_information[line][i], "01NSEW ")  == 0)
				error_exit_cube(cube, INVALID_MAZE_CHAR, map_information[line]);
			grid_maze[line][i] = map_information[line][i];
		}
		line++;
	}
}
