/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ory <ory@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 11:44:30 by egeorgel          #+#    #+#             */
/*   Updated: 2023/09/18 16:37:47 by ory              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
//# include <mlx.h>
# include "minilibx_opengl/mlx.h"
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <limits.h>
# include <math.h>
# include "libft/libft.h"

# define SIZE_OF_CASES 240
//multiples of 24 pls
# define WIN_X 1500
# define WIN_Y 900
# define MINIMAP_WALL_COLOR 0xAA2f2b2b
# define MINIMAP_FLOOR_COLOR 0xAAa49f9e
# define MINIMAP_PLAYER_COLOR 0xAAFF0000
# define MINIMAP_EMPTY_COLOR 0xFF000000
# define PI 3.14159265358979323846
# define FOV 60
# define RAD_DEGRE 0.0174533

typedef enum e_param_type
{
	INT_PARAM,
	STR_PARAM
}	t_param_type;

/*ERRORS*/

typedef enum e_err
{
	ERRMLX,
	ERRFILE,
	MISSING_PARAM,
	INVALID_PARAM,
	DOUBLE_PARAM,
	TOMANY_PARAM,
	PARAM_AFTER_MAP,
	NOMAP,
	NOPLAYER,
	MULTIPLE_PLAYERS,
	INVALID_MAP_CHARACTER,
	MAPHOLE,
	ERRCOLOR,
	NB_ARG,
	ERR_TEXT_FILE,
	ERR_TEXT_SIZE,
	ERRMAX,
}	t_err;

/*STRUCT*/

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}	t_img;

typedef struct s_keys
{
	bool	w;
	bool	s;
	bool	a;
	bool	d;
	bool	r_right;
	bool	r_left;
}	t_keys;

typedef struct s_coordinates
{
	double	x;
	double	y;
	int		dist_to_wall_limit;
	double	check_x;
	double	check_y;
}	t_coordinates;

typedef struct s_player
{
	t_coordinates	pos;
	double			angle;
	double			rad_angle;
}	t_player;

typedef struct s_mlx
{
	void	*mlx;
	void	*mlx_win;
}	t_mlx;

typedef struct s_minimap
{
	t_img	img;
	int		size_x;
	int		size_y;
}	t_minimap;

typedef struct s_texture
{
	t_img		img;
	double		wallx;
	double		texx;
	double		texy;
}	t_texture;

typedef struct s_param
{
	char			**map;
	char			*n_text;
	char			*s_text;
	char			*w_text;
	char			*e_text;
	t_texture		texture_north;
	t_texture		texture_south;
	t_texture		texture_west;
	t_texture		texture_east;
	t_texture		*texture;
	int				*floor_color;
	int				*ceiling_color;
}	t_param;

typedef struct s_draw_wall
{
	int	side_color;
	int	y;

	double	wall_height;
	double		wall_top;
	double		wall_bottom;
}	t_draw_wall;

typedef struct s_raycast_data
{
	double	ray_dir_x;
	double	ray_dir_y;
	double	angle_raycast_start;
	double	angle_raycast_end;
	double	x;
	double	y;
	double	angle_raycast_rad;
	double	new_ray_angle_rad;
	int	print_x;
	int	draw_y;
	double	dist_x;
	double	dist_y;
	int	mapx;
	int	mapy;
	int	side;
	double	dist_to_vertical;
	double	wall_dist;
	double	dist_to_horizontal;
	int	stepx;
	int	stepy;
}	t_raycast_data;

typedef struct s_mv
{
	double	x;
	double	y;
	double	dir_x;
	double	dir_y;
}	t_mv;

typedef struct s_cub
{
	t_mlx		mlx;
	t_param		params;
	t_player	player;
	t_keys		keys;
	t_minimap	minimap;
	char		**errors;
	t_draw_wall	wall_data;
	t_raycast_data	ray;
	t_img		view;
	int			win_x;
	int			win_y;
	double		mv_scaling;
	double		degre_to_rad;
	double		decrease_angle;
	double		dist_to_projection_plane;
}	t_cub;

/*PARSING*/
void	get_params(t_cub *cub, char *filename);
void	*get_param(t_cub *cub, char **file, char *param_name, int param_type);
void	get_map(t_cub *cub, char **file);
void	map_parse(t_cub *cub);
void	error_init(t_cub *cub);
void	error(t_cub *cub, int err, char *arg);
void	check_texture_size(t_cub *cub);
void	load_texture(t_cub *cub, t_texture *texture,
			char *file_path, char *error_msg);

/*MOVEMENT*/
bool	movement(t_cub *cub);
int		key_release(int keycode, t_cub *cub);
int		key_press(int keycode, t_cub *cub);

/*MINIMAP*/
void	get_minimap_size(t_cub *cub, int map_x_size, int map_y_size);
void	minimap_initialize(t_cub *cub);
void	minimap_update(t_cub *cub);

/*UTILS*/
int		line_size(char **line);
int		map_size(char **map);
char	*extract_second_word(t_cub *cub, char **line);
int		get_color(t_cub *cub, const char *str);
void	freetab(void **tab);
bool	empty_line(char *line);
void	create_image(t_mlx *mlx, t_img *img, int width, int height);
void	pixel_to_img(t_img *img, int x, int y, unsigned int color);
void	my_mlx_pixel_put(t_cub *cub, int x, int y, int color);

/*RENDERING*/
void	render(t_cub *cub);
void	set_texture(t_cub *cub);
int		cast_ray_horizontal(t_cub *cub);
int		cast_ray_vertical(t_cub *cub);
void	find_dist(t_cub *cub);
void	my_mlx_pixel_put(t_cub *cub, int x, int y, int color);
void	pixel_to_image(t_cub *cub);
void	draw_floor(t_cub *cub);
void	draw_sky(t_cub *cub);
void	draw_wall(double ray_dist, t_cub *cub);
void	init_wall(t_cub *cub, double ray_dist);
void	init_horizontal_step_distance(t_cub *cub);
void	init_vertical_step_distance(t_cub *cub);
void	ray_init_step_distance(t_cub *cub);
void	ray_var_init(t_cub *cub);

#endif