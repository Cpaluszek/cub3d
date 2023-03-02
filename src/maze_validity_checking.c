/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maze_validity_checking.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 13:08:18 by jlitaudo          #+#    #+#             */
/*   Updated: 2023/03/02 15:10:29 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "errors.h"
#include <math.h>

static void	check_first_and_last_column(t_cub3d *cube, char *line, int i);
static void	check_first_and_last_line(t_cub3d *cube, char *line);
static void	check_adjacent_cells(t_cub3d *cube, char **grid, int row, int col);
static void	set_player_starting_position(t_cub3d *cube, int i, int j);

void	maze_validity_checking(t_cub3d *cube, char **grid_maze)
{
	int	i;
	int	j;

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
				check_adjacent_cells(cube, grid_maze, j, i);
			if (ft_is_inside(grid_maze[j][i], "NSEW"))
				set_player_starting_position(cube, i, j);
			i++;
		}
		j++;
	}
}

static void	check_first_and_last_line(t_cub3d *cube, char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (ft_is_inside(line[i], "0NSEW"))
			error_exit_cube(cube, UNCLOSED_MAZE, line);
		i++;
	}
}

static void	check_adjacent_cells(t_cub3d *cube, char **grid, int row, int col)
{
	if (ft_is_inside(grid[row][col + 1], "0NSEW"))
		error_exit_cube(cube, UNCLOSED_MAZE, grid[row]);
	if (ft_is_inside(grid[row][col - 1], "0NSEW"))
		error_exit_cube(cube, UNCLOSED_MAZE, grid[row]);
	if (ft_is_inside(grid[row - 1][col], "0NSEW"))
		error_exit_cube(cube, UNCLOSED_MAZE, grid[row - 1]);
	if (ft_is_inside(grid[row + 1][col], "0NSEW"))
		error_exit_cube(cube, UNCLOSED_MAZE, grid[row + 1]);
}

static void	check_first_and_last_column(t_cub3d *cube, char *line, int i)
{
	if (ft_is_inside(line[i], "0NSEW"))
		error_exit_cube(cube, UNCLOSED_MAZE, line);
}

static void	set_player_starting_position(t_cub3d *cube, int i, int j)
{
	if (cube->player.pos.x != 0.0f || cube->player.pos.y != 0.0f)
		error_exit_cube(cube, SPAWNING, "aborting execution");
	cube->player.pos.x = (float) i;
	cube->player.pos.y = (float) j;
	if (cube->grid_maze[j][i] == 'N')
	{
		cube->player.dir.x = 0.0f;
		cube->player.dir.y = -1.0f;
		cube->player.angle = 3 * PI / 2;
	}
	else if (cube->grid_maze[j][i] == 'S')
	{
		cube->player.dir.x = 0.0f;
		cube->player.dir.y = 1.0f;
		cube->player.angle = PI / 2;
	}
	if (cube->grid_maze[j][i] == 'E')
	{
		cube->player.dir.x = 1.0f;
		cube->player.dir.y = 0.0f;
		cube->player.angle = 0;
	}
	if (cube->grid_maze[j][i] == 'W')
	{
		cube->player.dir.x = -1.0f;
		cube->player.dir.y = 0.0f;
		cube->player.angle = PI;
	}
	cube->player.dir.x = cos(cube->player.angle);
	cube->player.dir.y = sin(cube->player.angle);
	cube->grid_maze[j][i] = '0';
}
