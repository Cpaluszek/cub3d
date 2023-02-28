/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 18:41:15 by jlitaudo          #+#    #+#             */
/*   Updated: 2023/02/28 10:48:40 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include "cub3d.h"
#include "libft.h"

static void	parse_map_information(t_cub3d *cube, int fd_map);
static void	interpret_map_information(t_cub3d *cube, char **map_information);
static void	create_maze(t_cub3d *cube, char **map_information);
static void	fill_maze(char **grid_maze, char **map_information);
static int	maze_validity_checking(char **grid_maze);

//todo : envisager le cas d'un fichier vide;

void	central_parsing(t_cub3d *cube)
{
	int	fd_map;

	fd_map = open(cube->map_path, O_RDONLY);
	if (fd_map == -1)
		error_exit_cube(cube, ERR_PATH, strerror(errno));
	cube->map_display.north_texture = NULL;
	cube->map_display.south_texture = NULL;
	cube->map_display.west_texture = NULL;
	cube->map_display.east_texture = NULL;
	// Todo: define base color
	cube->map_display.ceiling_color.color = 20000000;
	cube->map_display.floor_color.color = 20000000;
	parse_map_information(cube, fd_map);
//    map_information_checking(cube);
}

static void	parse_map_information(t_cub3d *cube, int fd_map)
{
	char	buffer[1000000];
	ssize_t	nb_read;
	char	**map_information;

	nb_read = read(fd_map, buffer, 1000000);
	dprintf(2, "read: %s\n", buffer);
	// Todo: check read return
	(void) nb_read;
//	empty_file_checking(read, buffer);
	map_information = ft_split(buffer, '\n');
	test_failed_malloc(cube, map_information);
	interpret_map_information(cube, map_information);
//    parse_maze(line, cube, fd_map);
}

static void	interpret_map_information(t_cub3d *cube, char **map_information)
{
	int	i;

	i = 0;
	while (i < 6)
	{
		find_texture_path_and_get_color(cube, map_information[i]);
		i++;
	}
	create_maze(cube, &map_information[i]);
	fill_maze(cube->grid_maze, &map_information[i]);
	print_maze(cube->grid_maze);
	if (maze_validity_checking(cube->grid_maze) == ERROR)
		exit_cube(cube, EXIT_FAILURE);
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
		cube->grid_maze[i][len_max - 1] = '\0';
		i++;
	}
}

static void	fill_maze(char **grid_maze, char **map_information)
{
	int		line;
	int		i;

	line = 0;
	while (map_information[line])
	{
		i = -1;
		while (map_information[line][++i])
			grid_maze[line][i] = map_information[line][i];
		line++;
	}
}

static int	maze_validity_checking(char **grid_maze)
{
	int	i;

	i = -1;
	// TOdo:
	while (grid_maze[0][++i])
		if (grid_maze[0][i] != ' ' && grid_maze[0][i] != '1')
			return (ERROR);
//			return (print_error_maze(maze[0]));
	return(SUCCESS);
}
