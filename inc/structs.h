#ifndef STRUCTS_H
#define STRUCTS_H

# include "mlx_utils.h"
# include "cub3d.h"

// Todo: double or float ?
typedef struct	s_vector {
	float	x;
	float	y;
}	t_vector;

typedef struct	s_player {
	t_vector	pos;
	t_vector	dir;
}	t_player;

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

typedef struct s_map_data
{
	char	*north_texture;
	char	*south_texture;
	char	*west_texture;
	char	*east_texture;
	t_color	floor_color;
	t_color	ceiling_color;
}	t_map_data;

typedef struct	s_mlx_data {
	void		*mlx;
	void		*mlx_win;
	void		*mlx_img;
	t_img_data	img1;
	t_img_data	img2;
	t_img_data	*current_img;
	t_img_data	*working_img;
}	t_mlx_data;

typedef struct s_cub3d
{
	// Note: remove map_path from struct
	char		*map_path;
	char		**grid_maze;
	// Note: remove from struct ??
	char		**map_information;
	t_map_data	map_data;
	t_mlx_data	mlx_data;
	t_player	player;
	float 		screen_width;
	// Note: try to use previous defines
	int			raysize[1920];
	char		raytexture[1920];
}	t_cub3d;

enum e_result
{
	SUCCESS = 0,
	ERROR = 1,
};

#endif
