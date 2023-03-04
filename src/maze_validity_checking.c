/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maze_validity_checking.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlitaudo <jlitaudo@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 13:08:18 by jlitaudo          #+#    #+#             */
/*   Updated: 2023/03/03 14:01:18 by jlitaudo         ###   ########.fr       */
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
	int	col;
	int	row;

	row = 0;
	while (grid_maze[row])
	{
		col = 0;
		while (grid_maze[row][col])
		{
			if (row == 0 || grid_maze[row + 1] == NULL)
				check_first_and_last_line(cube, grid_maze[row]);
			else if (col == 0 || col == cube->map_display.maze_width - 1)
				check_first_and_last_column(cube, grid_maze[row], col);
			if (grid_maze[row][col] == ' ')
				check_adjacent_cells(cube, grid_maze, row, col);
			if (ft_is_inside(grid_maze[row][col], "NSEW"))
				set_player_starting_position(cube, col, row);
			col++;
		}
		row++;
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
	if (col != cube->map_display.maze_width - 1 && \
		ft_is_inside(grid[row][col + 1], "0NSEW"))
		error_exit_cube(cube, UNCLOSED_MAZE, grid[row]);
	if (col != 0 && ft_is_inside(grid[row][col - 1], "0NSEW"))
		error_exit_cube(cube, UNCLOSED_MAZE, grid[row]);
	if (row != 0 && ft_is_inside(grid[row - 1][col], "0NSEW"))
		error_exit_cube(cube, UNCLOSED_MAZE, grid[row - 1]);
	if (grid[row +1] && ft_is_inside(grid[row + 1][col], "0NSEW"))
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
	if (cube->map_display.grid_maze[j][i] == 'N')
		cube->player.angle = 3 * M_PI_2;
	else if (cube->map_display.grid_maze[j][i] == 'S')
		cube->player.angle = M_PI_2;
	else if (cube->map_display.grid_maze[j][i] == 'E')
		cube->player.angle = 0;
	else if (cube->map_display.grid_maze[j][i] == 'W')
		cube->player.angle = M_PI;
	cube->player.dir.x = cos(cube->player.angle);
	cube->player.dir.y = sin(cube->player.angle);
	cube->map_display.grid_maze[j][i] = '0';
}
