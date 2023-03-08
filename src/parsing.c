/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 18:41:15 by jlitaudo          #+#    #+#             */
/*   Updated: 2023/03/08 14:39:42 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include "errors.h"
#include "cub3d.h"

#define BUF_SIZE 1000000
#define DEFAULT_COLOR_VALUE 0x01000000
#define FORMAT ".cub"

static void	set_default_values(t_cub3d *cube);
static void	parse_map_information(t_cub3d *cube, int fd_map);
static void	check_no_gap_in_maze(t_cub3d *cube, char **map_info, char *buff);

void central_parsing(t_cub3d *cube, char *map_path)
{
	int		fd_map;
	char	*format;

	set_default_values(cube);
	format = ft_strnstr(map_path, FORMAT, ft_strlen(map_path));
	if (!format || format[4] != '\0')
		error_exit_cube(cube, ERR_FORMAT, "");
	fd_map = open(map_path, O_RDONLY);
	if (fd_map == -1)
		error_exit_cube(cube, map_path, strerror(errno));
	parse_map_information(cube, fd_map);
}

static void	set_default_values(t_cub3d *cube)
{
	cube->textures_paths.north_texture_path = NULL;
	cube->textures_paths.south_texture_path = NULL;
	cube->textures_paths.west_texture_path = NULL;
	cube->textures_paths.east_texture_path = NULL;
	cube->display.grid_maze = NULL;
	cube->display.ceiling_color.color = DEFAULT_COLOR_VALUE;
	cube->display.floor_color.color = DEFAULT_COLOR_VALUE;
	cube->player.pos.x = 0.0f;
	cube->player.pos.y = 0.0f;
}

static void	parse_map_information(t_cub3d *cube, int fd_map)
{
	char	buffer[BUF_SIZE];
	ssize_t	nb_read;
	char 	**map_information;

	nb_read = read(fd_map, buffer, BUF_SIZE);
	if (nb_read == -1)
	{
		close(fd_map);
		error_exit_cube(cube, ERR_READ, "");
	}
	close(fd_map);
	map_information = ft_split(buffer, '\n');
	test_failed_malloc(cube, map_information);
	check_no_gap_in_maze(cube, map_information, buffer);
	interpret_map_information(cube, map_information);
	ft_free_split(map_information);
}

static void	check_no_gap_in_maze(t_cub3d *cube, char **map_info, char *buff)
{
	int	i;
	int	j;

	i = 0;
	while (map_info[i])
	{
		j = 0;
		while (map_info[i][j] && ft_is_inside(map_info[i][j], "01NSEW "))
			j++;
		if (map_info[i][j] == '\0')
			break ;
		i++;
	}
	buff = ft_strnstr(buff, map_info[i], ft_strlen(buff));
	buff = ft_strnstr(buff, "\n\n", ft_strlen(buff));
	if (!buff)
		return ;
	i = 0;
	while (buff[i])
	{
		if (buff[i] != '\n')
			error_exit_cube(cube, ERR_MAZE, UNEXPECTED_NEWLINE_MAZE);
		i++;
	}
}
