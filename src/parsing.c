/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 18:41:15 by jlitaudo          #+#    #+#             */
/*   Updated: 2023/03/10 10:49:49 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include "errors.h"
#include "cub3d.h"

#define BUFF_SIZE 1000000
#define FORMAT ".cub"

static void	parse_map_information(t_cub3d *cube, int fd_map);
static void	check_no_gap_in_maze(t_cub3d *cube, char **map_info, char *buff);

void	central_parsing(t_cub3d *cube, char *map_path)
{
	int		fd_map;
	char	*format;

	format = ft_strnstr(map_path, FORMAT, ft_strlen(map_path));
	if (!format || format[4] != '\0')
		error_exit_cube(cube, ERR_FORMAT, "");
	fd_map = open(map_path, O_RDONLY);
	if (fd_map == -1)
		error_exit_cube(cube, map_path, strerror(errno));
	parse_map_information(cube, fd_map);
}

static void	parse_map_information(t_cub3d *cube, int fd_map)
{
	char	buffer[BUFF_SIZE];
	ssize_t	nb_read;

	ft_memset(buffer, 0, BUFF_SIZE);
	nb_read = read(fd_map, buffer, BUFF_SIZE);
	if (nb_read == -1)
	{
		close(fd_map);
		error_exit_cube(cube, ERR_READ, "");
	}
	close(fd_map);
	cube->map_info = ft_split(buffer, '\n');
	test_failed_malloc(cube, cube->map_info);
	check_no_gap_in_maze(cube, cube->map_info, buffer);
	interpret_map_information(cube, cube->map_info);
}

static void	check_no_gap_in_maze(t_cub3d *cube, char **map_info, char *buff)
{
	int	i;
	int	j;

	i = 0;
	while (map_info[i])
	{
		j = 0;
		while (map_info[i][j] && ft_is_inside(map_info[i][j], GRID_CHARSET))
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
