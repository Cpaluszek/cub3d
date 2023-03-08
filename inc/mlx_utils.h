/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 15:49:06 by cpalusze          #+#    #+#             */
/*   Updated: 2023/03/08 13:31:00 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_UTILS_H
# define MLX_UTILS_H

# include "../lib/minilibx-linux/mlx.h"

typedef struct s_img_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img_data;

typedef struct s_mlx_texture {
	void *address;
	char *text;
	int bits_per_pixel;
	int line_length;
	int endian;
	int width;
	int height;
} t_mlx_texture;

// Todo: remove useless
enum	e_key_codes
{
	KEY_A = 97,
	KEY_S = 115,
	KEY_D = 100,
	KEY_Q = 113,
	KEY_W = 119,
	KEY_E = 101,
	KEY_R = 114,
	KEY_I = 105,
	KEY_P = 112,
	LEFT_ANGLE_BRACKET = 43,
	RIGHT_ANGLE_BRACKET = 47,
	SPACE = 32,
	ESC = 65307,
	KEY_1 = 18,
	KEY_2 = 19,
	KEY_3 = 20,
	KEY_4 = 21,
	KEY_5 = 23,
	NUM_PAD_0 = 82,
	NUM_PAD_1 = 83,
	NUM_PAD_2 = 84,
	NUM_PAD_3 = 85,
	NUM_PAD_4 = 86,
	NUM_PAD_5 = 87,
	NUM_PAD_6 = 88,
	NUM_PAD_7 = 89,
	NUM_PAD_8 = 91,
	NUM_PAD_9 = 92,
	NUM_PAD_PLUS = 69,
	NUM_PAD_MINUS = 78,
	ARROW_UP = 65362,
	ARROW_DOWN = 65364,
	ARROW_LEFT = 65361,
	ARROW_RIGHT = 65363
};

enum	e_mouse_codes
{
	MOUSE_LEFT = 1,
	MOUSE_RIGHT = 2,
	MOUSE_MIDDLE = 3,
	SCROLL_DOWN = 4,
	SCROLL_UP = 5
};

enum	e_mlx_events
{
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSE_DOWN = 4,
	ON_MOUSE_UP = 5,
	ON_MOUSE_MOVE = 6,
	ON_BUTTON_PRESS = 17
};

void	my_mlx_pixel_put(t_img_data *img_data, int x, int y, int color);

#endif
