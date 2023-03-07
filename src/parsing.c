/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlitaudo <jlitaudo@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 18:41:15 by jlitaudo          #+#    #+#             */
/*   Updated: 2023/03/03 20:14:12 by jlitaudo         ###   ########.fr       */
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

void	central_parsing(t_cub3d *cube)
{
	int		fd_map;
	char	*format;

	set_default_values(cube);
	format = ft_strnstr(cube->map_path, FORMAT, ft_strlen(cube->map_path));
	if (!format || format[4] != '\0')
		error_exit_cube(cube, ERR_FORMAT, "");
	fd_map = open(cube->map_path, O_RDONLY);
	if (fd_map == -1)
		error_exit_cube(cube, cube->map_path, strerror(errno));
	parse_map_information(cube, fd_map);
	create_texture_array(cube);
}

static void	set_default_values(t_cub3d *cube)
{
	cube->map_data.north_texture_path = NULL;
	cube->map_data.south_texture_path = NULL;
	cube->map_data.west_texture_path = NULL;
	cube->map_data.east_texture_path = NULL;
	cube->map_display.grid_maze = NULL;
	cube->map_information = NULL;
	cube->map_display.ceiling_color.color = DEFAULT_COLOR_VALUE;
	cube->map_display.floor_color.color = DEFAULT_COLOR_VALUE;
	cube->player.pos.x = 0.0f;
	cube->player.pos.y = 0.0f;
}

static void	parse_map_information(t_cub3d *cube, int fd_map)
{
	char	buffer[BUF_SIZE];
	ssize_t	nb_read;

	nb_read = read(fd_map, buffer, BUF_SIZE);
	if (nb_read == -1)
	{
		close(fd_map);
		error_exit_cube(cube, ERR_READ, "");
	}
	close(fd_map);
	cube->map_information = ft_split(buffer, '\n');
	test_failed_malloc(cube, cube->map_information);
	check_no_gap_in_maze(cube, cube->map_information, buffer);
	interpret_map_information(cube, cube->map_information);
	ft_free_split(cube->map_information);
	cube->map_information = NULL;
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
