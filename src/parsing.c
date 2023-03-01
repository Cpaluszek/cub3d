/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlitaudo <jlitaudo@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 18:41:15 by jlitaudo          #+#    #+#             */
/*   Updated: 2023/03/01 11:46:06 by jlitaudo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <math.h>
#include "errors.h"
#include "cub3d.h"

#define BUF_SIZE 1000000

static void	parse_map_information(t_cub3d *cube, int fd_map);
static void	check_no_splitted_maze(t_cub3d *cube, char **map_information, char *buffer);

void	central_parsing(t_cub3d *cube)
{
	int		fd_map;
	char	*extension;

	extension = ft_strnstr(cube->map_path, ".cub", ft_strlen(cube->map_path));
	if (!extension || extension[4] != '\0')
		error_exit_cube(cube, ERR_FORMAT, "");
    fd_map = open(cube->map_path, O_RDONLY);
	if (fd_map == -1)
		error_exit_cube(cube, cube->map_path, strerror(errno));
	cube->map_data.north_texture = NULL;
	cube->map_data.south_texture = NULL;
	cube->map_data.west_texture = NULL;
	cube->map_data.east_texture = NULL;
	cube->map_data.ceiling_color.color = 0x01000000;
	cube->map_data.floor_color.color = 0x01000000;
	cube->grid_maze = NULL;
	cube->player.pos.x = 0.0f;
	cube->player.pos.y = 0.0f;
	cube->screen_width = SCREEN_DISTANCE * tan(FOV / 2) * 2;
	parse_map_information(cube, fd_map);
}

static void	parse_map_information(t_cub3d *cube, int fd_map)
{
	char	buffer[BUF_SIZE];
	ssize_t	nb_read;

	nb_read = read(fd_map, buffer, BUF_SIZE);
	if (nb_read == -1)
		error_exit_cube(cube, ERR_READ, "");
	cube->map_information = ft_split(buffer, '\n');
	test_failed_malloc(cube, cube->map_information);
	check_no_splitted_maze(cube, cube->map_information, buffer);
	interpret_map_information(cube, cube->map_information);
	ft_free_split(cube->map_information);
	cube->map_information = NULL;
}

static void	check_no_splitted_maze(t_cub3d *cube, char **map_information, char *buffer)
{
	int i;
	int j;

	i = 0;
	while (map_information[i])
	{
		j = 0;
		while (map_information[i][j] && ft_is_inside(map_information[i][j], "01NSEW "))
			j++;
		if (map_information[i][j] == '\0')
			break;
		i++;
	}
	buffer = ft_strnstr(buffer, map_information[i], ft_strlen(buffer));
	buffer = ft_strnstr(buffer, "\n\n", ft_strlen(buffer));
	if (!buffer)
		return ;
	i = 0;
	while (buffer[i])
	{
		if (buffer[i] != '\n')
			error_exit_cube(cube, ERR_MAZE, "newline inside");
		i++;
	}
}
