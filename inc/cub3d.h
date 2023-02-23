/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlitaudo <jlitaudo@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 13:32:59 by cpalusze          #+#    #+#             */
/*   Updated: 2023/02/23 18:40:52 by jlitaudo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include "libft.h"
# include "../lib/minilibx-linux/mlx.h"

# define LOS_ANGLE 120
# define MAX LOS 10

typedef struct s_general{

    char    *map_path;
    short   **grid_maze;
    t_map   map_display;
    int     view_angle;

}t_general;

typedef struct s_map{
    char    *north_texture;
    char    *south_texture;
    char    *west_texture;
    char    *east_texture;
    t_color floor_color;
    t_color ceiling_color;
}t_map;

typedef union u_color{
    char
}t_color;

# define WIN_WIDTH	1920
# define WIN_HEIGHT	1080
# define WIN_NAME	"cub3D"

enum e_result {
    SUCCESS = 0,
    ERROR = 1,
};

#endif