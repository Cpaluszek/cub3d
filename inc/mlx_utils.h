/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 15:49:06 by cpalusze          #+#    #+#             */
/*   Updated: 2023/02/23 15:53:50 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_UTILS_H
# define MLX_UTILS_H

typedef struct s_img_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img_data;

enum	e_key_codes
{
	KEY_A = 0,
	KEY_S = 1,
	KEY_D = 2,
	KEY_Q = 12,
	KEY_W = 13,
	KEY_E = 14,
	KEY_R = 15,
	KEY_I = 34,
	KEY_P = 35,
	LEFT_ANGLE_BRACKET = 43,
	RIGHT_ANGLE_BRACKET = 47,
	SPACE = 49,
	ESC = 53,
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
	ARROW_UP = 126,
	ARROW_DOWN = 125,
	ARROW_LEFT = 124,
	ARROW_RIGHT = 123
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
	ON_BUTTON_PRESS = 17
};

void	my_mlx_pixel_put(t_img_data *img_data, int x, int y, int color);

#endif
