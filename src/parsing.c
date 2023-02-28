/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Teiki <Teiki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 18:41:15 by jlitaudo          #+#    #+#             */
/*   Updated: 2023/02/27 23:17:56 by Teiki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include "cub3d.h"
#include "libft.h"

void	parse_map_information(t_cub3d *cube, int fd_map);
void	interpret_map_information(t_cub3d *cube, char **map_information);

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
	cube->map_display.ceiling_color.color = 20000000;
	cube->map_display.floor_color.color = 20000000;
	parse_map_information(cube, fd_map);
//    map_information_checking(cube);
}

void	parse_map_information(t_cub3d *cube, int fd_map)
{
	char	buffer[1000000];
	int		nb_read;
	char	**map_information;
	int		i;

	nb_read = read(fd_map, buffer, 1000000);
//	empty_file_checking(read, buffer);
	map_information = ft_split(buffer, '\n');
	test_failed_malloc(cube, map_information);
	interpret_map_information(cube, map_information);
//    parse_maze(line, cube, fd_map);
}

void	interpret_map_information(t_cub3d *cube, char **map_information)
{
	int	i;
	int	j;

	i = 0;
	while (i < 6)
	{
		find_texture_path_and_get_color(cube, map_information[i]);
		i++;
	}
	create_maze(cube, &map_information[i]);
	fill_maze(cube->grid_maze, &map_information[i]);
	if (maze_validity_checking(cube->grid_maze) == ERROR)
		exit_cube(cube);
}

void	create_maze(t_cub3d *cube, char **map_information)
{
	int	i;
	int	len;
	int	len_max;

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
	cube->grid_maze[i + 1] = NULL;
	i = 0;
	while (cube->grid_maze[i])
	{
		cube->grid_maze[i] = malloc(sizeof(char) * len_max);
		test_failed_malloc(cube, cube->grid_maze[i]);
		ft_memset(cube->grid_maze[i], ' ', len_max);
	}
}

void	fill_maze(char **grid_maze, char **map_information)
{
	char	*str;
	int		line;
	int		i;

	line = 0;
	str = map_information[line];
	while (str)
	{
		i = -1;
		while (str[++i])
			grid_maze[line][i] = str[i];
		line++;
		str = map_information[line];
	}
}

int	maze_validity_checking(char **grid_maze)
{
	int	line;
	int	i;

	i = -1;
	while (grid_maze[0][++i])
		if (grid_maze[0][i] != ' ' && grid_maze[0][i] != '1')
			return (print_error_maze(maze[0]))
	line = 0;

}
