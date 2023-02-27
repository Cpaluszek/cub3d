/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Teiki <Teiki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 18:41:15 by jlitaudo          #+#    #+#             */
/*   Updated: 2023/02/27 17:00:50 by Teiki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include "cub3d.h"
#include "libft.h"

void	parse_map_information(t_general *cube, int fd_map);
void	interpret_map_information(t_general *cube, char **map_information);

//todo : envisager le cas d'un fichier vide;

void	central_parsing(t_general *cube)
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

void	parse_map_information(t_general *cube, int fd_map)
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

void	interpret_map_information(t_general *cube, char **map_information)
{
	int	i;

	i = 0;
	while (i < 6)
	{
		find_texture_path_and_get_color(cube, map_information[i]);
		i++;
	}
//	parse_maze(line, cube, fd_map);
}
