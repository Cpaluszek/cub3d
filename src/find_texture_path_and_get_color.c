
#include "cub3d.h"
#include "libft.h"

static void	parse_color(t_general *cube, t_rgb *color, char *line);
static int	get_color(unsigned char *p_color, char **p_line);
static char	*retrieve_path(t_general *cube, char *line, char *pattern);
static void	retrieve_color(t_general *cube, t_rgb *color, \
	char *line, char *pattern);

void	find_texture_path_and_get_color(t_general *cube, char *line)
{
	int	len;

	len = ft_strlen(line);
	if (ft_strnstr(line, "NO ", len) != NULL)
		cube->map_display.north_texture = retrieve_path(cube, line, "NO ");
	else if (ft_strnstr(line, "SO ", len) != NULL)
		cube->map_display.north_texture = retrieve_path(cube, line, "SO ");
	else if (ft_strnstr(line, "WE ", len) != NULL)
		cube->map_display.north_texture = retrieve_path(cube, line, "WE ");
	else if (ft_strnstr(line, "EA ", len) != NULL)
		cube->map_display.north_texture = retrieve_path(cube, line, "EA ");
	else if (ft_strnstr(line, "F ", len) != NULL)
		retrieve_color(cube, &cube->map_display.floor_color.rgb, line, "F ");
	else if (ft_strnstr(line, "C ", len) != NULL)
		retrieve_color(cube, &cube->map_display.ceiling_color.rgb, line, "C ");
	else
		error_exit_cube(cube, INVALID_FILE_PARAM, line);
}

static char	*retrieve_path(t_general *cube, char *line, char *pattern)
{
	char	*path;
	int		i;

	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	if (ft_strncmp(&line[i], pattern, 3) == ERROR)
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

static void	retrieve_color(t_general *cube, \
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
	parse_color(cube, color, line);
}

static void	parse_color(t_general *cube, t_rgb *color, char *line)
{
	if (get_color(&color->red, &line) == ERROR)
		error_exit_cube(cube, INVALID_COLOR, line);
	if (get_color(&color->gre, &line) == ERROR)
		error_exit_cube(cube, INVALID_COLOR, line);
	if (get_color(&color->blu, &line) == ERROR)
		error_exit_cube(cube, INVALID_COLOR, line);
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
	*p_line = &line[i + 1];
	*p_color = color;
	return (SUCCESS);
}
