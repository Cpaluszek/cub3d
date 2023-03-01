#ifndef STRUCTS_H
#define STRUCTS_H

# include "mlx_utils.h"

typedef struct s_rgb
{
	unsigned char	blu;
	unsigned char	gre;
	unsigned char	red;
}t_rgb;

typedef union u_color
{
	unsigned int	color;
	t_rgb			rgb;
}	t_color;

typedef struct	s_dvector {
	double	x;
	double	y;
}	t_dvector;

typedef struct s_map
{
	char	*north_texture;
	char	*south_texture;
	char	*west_texture;
	char	*east_texture;
	t_color	floor_color;
	t_color	ceiling_color;
}	t_map;

typedef struct	s_mlx_data {
	void		*mlx;
	void		*mlx_win;
	void		*mlx_img;
	t_img_data	img;
}	t_mlx_data;

typedef struct s_cub3d
{
	char		*map_path;
	char		**grid_maze;
	char		**map_information;
	t_map		map_display;
	int			view_angle;
	t_mlx_data	mlx_data;
}	t_cub3d;

enum e_result
{
	SUCCESS = 0,
	ERROR = 1,
};

#endif
