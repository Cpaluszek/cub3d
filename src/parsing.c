/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 18:41:15 by jlitaudo          #+#    #+#             */
/*   Updated: 2023/03/10 10:19:34 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include "errors.h"
#include "cub3d.h"

#define BUF_SIZE 1000000
#define FORMAT ".cub"

static void	parse_map_information(t_cub3d *cube, int fd_map);
static void	check_no_gap_in_maze(t_cub3d *cube, char *buff);

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
	char	buffer[BUF_SIZE];
	ssize_t	nb_read;

	ft_memset(buffer, 0, BUF_SIZE);
	nb_read = read(fd_map, buffer, BUF_SIZE);
	if (nb_read == -1)
	{
		close(fd_map);
		error_exit_cube(cube, ERR_READ, "");
	}
	close(fd_map);
	cube->map_info = ft_split(buffer, '\n');
	test_failed_malloc(cube, cube->map_info);
	check_no_gap_in_maze(cube, buffer);
	interpret_map_information(cube);
}

static void	check_no_gap_in_maze(t_cub3d *cube, char *buff)
{
	int	i;
	int	j;

	i = -1;
	while (cube->map_info[++i])
	{
		j = 0;
		while (cube->map_info[i][j] && ft_is_inside(cube->map_info[i][j], \
			GRID_CHARSET))
			j++;
		if (cube->map_info[i][j] == '\0')
			break ;
	}
	buff = ft_strnstr(buff, cube->map_info[i], ft_strlen(buff));
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
