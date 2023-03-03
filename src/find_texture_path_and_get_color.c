/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_texture_path_and_get_color.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlitaudo <jlitaudo@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 15:15:00 by cpalusze          #+#    #+#             */
/*   Updated: 2023/03/03 11:46:41 by jlitaudo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "errors.h"
#include "libft.h"

static void	parse_color(t_cub3d *cube, t_rgb *color, char **p_line);
static int	get_color(unsigned char *p_color, char **p_line);
static char	*retrieve_path(t_cub3d *cube, char *line, char *pattern);
static void	retrieve_color(t_cub3d *cube, t_rgb *color, \
	char *line, char *pattern);

//todo : parse spaces in color

void	find_texture_path_and_get_color(t_cub3d *cube, char *line)
{
	size_t	len;

	len = ft_strlen(line);
	if (ft_strnstr(line, "NO ", len) != NULL && cube->map_data.north_texture_path == NULL)
		cube->map_data.north_texture_path = retrieve_path(cube, line, "NO ");
	else if (ft_strnstr(line, "SO ", len) != NULL && cube->map_data.south_texture_path == NULL)
		cube->map_data.south_texture_path = retrieve_path(cube, line, "SO ");
	else if (ft_strnstr(line, "WE ", len) != NULL && cube->map_data.west_texture_path == NULL)
		cube->map_data.west_texture_path = retrieve_path(cube, line, "WE ");
	else if (ft_strnstr(line, "EA ", len) != NULL && cube->map_data.east_texture_path == NULL)
		cube->map_data.east_texture_path = retrieve_path(cube, line, "EA ");
	else if (ft_strnstr(line, "F ", len) != NULL && cube->map_data.floor_color.color == 0x01000000)
		retrieve_color(cube, &cube->map_data.floor_color.rgb, line, "F ");
	else if (ft_strnstr(line, "C ", len) != NULL && cube->map_data.ceiling_color.color == 0x01000000)
		retrieve_color(cube, &cube->map_data.ceiling_color.rgb, line, "C ");
	else
		error_exit_cube(cube, INVALID_PARAM, line);
}

static char	*retrieve_path(t_cub3d *cube, char *line, char *pattern)
{
	char	*path;
	int		i;

	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	if (ft_strncmp(&line[i], pattern, 3))
		error_exit_cube(cube, INVALID_TEXT_FILE_PATTERN, line);
	line = &line[i + 3];
	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	if (!line[i])
		error_exit_cube(cube, EMPTY_PATTERN, line);
	line = &line[i];
	i = 0;
	while (line[i] && line[i] != ' ' && line[i] != '\n')
		i++;
	path = ft_strndup(line, i);
	test_failed_malloc(cube, path);
	return (path);
}

static void	retrieve_color(t_cub3d *cube, \
	t_rgb *color, char *line, char *pattern)
{
	int		i;

	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	if (ft_strncmp(&line[i], pattern, 2) == ERROR)
		error_exit_cube(cube, INVALID_TEXT_FILE_PATTERN, line);
	line = &line[i + 2];
	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	if (!line[i])
		error_exit_cube(cube, EMPTY_PATTERN, line);
	line = &line[i];
	parse_color(cube, color, &line);
}

static void	parse_color(t_cub3d *cube, t_rgb *color, char **p_line)
{
	char	*line;

	line = *p_line;
	if (get_color(&color->red, &line) == ERROR)
		error_exit_cube(cube, INVALID_COLOR, *p_line);
	if (get_color(&color->gre, &line) == ERROR)
		error_exit_cube(cube, INVALID_COLOR, *p_line);
	if (get_color(&color->blu, &line) == ERROR)
		error_exit_cube(cube, INVALID_COLOR, *p_line);
}

static int	get_color(unsigned char *p_color, char **p_line)
{
	int		i;
	int		color;
	char	*line;

	line = *p_line;
	i = 0;
	while (line[i] && ft_isdigit(line[i]))
		i++;
	color = ft_atoi(line);
	if (i > 3 || i == 0 || color > 255)
		return (ERROR);
	if (line[i])
		i++;
	while (line[i] && line[i] == ' ')
		i++;
	*p_line = &line[i];
	*p_color = color;
	return (SUCCESS);
}
