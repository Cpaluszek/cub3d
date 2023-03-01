/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maze_validity_checking.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlitaudo <jlitaudo@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 13:08:18 by jlitaudo          #+#    #+#             */
/*   Updated: 2023/02/28 13:50:54 by jlitaudo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "errors.h"

static void check_first_and_last_column(t_cub3d *cube, char *line, int i);
static void check_first_and_last_line(t_cub3d *cube, char *line);
static void check_prev_next_up_and_down(t_cub3d *cube, char **grid_maze, int line, int column);

void	maze_validity_checking(t_cub3d *cube, char **grid_maze)
{
	int	i;
	int j;
	int count;

	count = 0;
	j = 0;
	while (grid_maze[j])
	{
		i = 0;
		while (grid_maze[j][i])
		{
			if (j == 0 || grid_maze[j + 1] == NULL)
				check_first_and_last_line(cube, grid_maze[j]);
			else if (i == 0 || grid_maze[j][i + 1] == '\0')
				check_first_and_last_column(cube, grid_maze[j], i);
			else if (grid_maze[j][i] == ' ')
				check_prev_next_up_and_down(cube, grid_maze, j, i);
			if (ft_is_inside(grid_maze[j][i], "NSEW"))
				count++;
			i++;
		}
		j++;
	}
	if (count != 1)
		error_exit_cube(cube, SPAWNING, "");
}

static void check_first_and_last_line(t_cub3d *cube, char *line)
{
	int i;

	i = 0;
	while (line[i])
	{
		if (ft_is_inside(line[i], "0NSEW"))
			error_exit_cube(cube, UNCLOSED_MAZE, line);
		i++;
	}
}

static void check_prev_next_up_and_down(t_cub3d *cube, char **grid_maze, int line, int column)
{
	if (ft_is_inside(grid_maze[line][column + 1], "0NSEW"))
		error_exit_cube(cube, UNCLOSED_MAZE, grid_maze[line]);
	if (ft_is_inside(grid_maze[line][column - 1], "0NSEW"))
		error_exit_cube(cube, UNCLOSED_MAZE, grid_maze[line]);
	if (ft_is_inside(grid_maze[line - 1][column], "0NSEW"))
		error_exit_cube(cube, UNCLOSED_MAZE, grid_maze[line - 1]);
	if (ft_is_inside(grid_maze[line + 1][column], "0NSEW"))
		error_exit_cube(cube, UNCLOSED_MAZE, grid_maze[line + 1]);
}

static void check_first_and_last_column(t_cub3d *cube, char *line, int i)
{
	if (ft_is_inside(line[i], "0NSEW"))
		error_exit_cube(cube, UNCLOSED_MAZE, line);
}
