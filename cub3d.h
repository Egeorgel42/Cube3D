/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ory <ory@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 11:44:30 by egeorgel          #+#    #+#             */
/*   Updated: 2023/09/11 00:17:27 by ory              ###   ########.fr       */
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

# define SIZE_OF_CASES 48
//multiples of 24 pls
# define MV_SCALING 2
# define WIN_X 1500
# define WIN_Y 900
# define MINIMAP_WALL_COLOR 0xAA2f2b2b
# define MINIMAP_FLOOR_COLOR 0xAAa49f9e
# define MINIMAP_PLAYER_COLOR 0xAAFF0000
# define MINIMAP_EMPTY_COLOR 0xFF000000
# define PI 3.14159265358979323846
# define DEGRE_TO_RAD PI / 180

# define FOV 60
# define PLAYER_HEIGHT SIZE_OF_CASES / 2

# define RAD_DEGRE 0.0174533
# define DECREASE_ANGLE (FOV * (PI / 180))/WIN_X
# define DIST_TO_PROJECTION_PLANE (WIN_X / 2) / (tan(FOV * DEGRE_TO_RAD/2))

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
	ERRMAX,
}	t_err;

/*STRUCT*/

typedef struct s_img
{
	void	*img;
	char	*addr;
	int	bits_per_pixel;
	int	line_length;
	int	endian;
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
}	t_coordinates;

typedef struct s_player
{
	t_coordinates	pos;
	double		angle;
	double		rad_angle;
}	t_player;

typedef struct s_mlx
{
	void	*mlx;
	void	*mlx_win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_mlx;

typedef struct s_minimap
{
	t_img	img;
	int		size_x;
	int		size_y;
}	t_minimap;

typedef struct s_param
{
	char			**map;
	char			*n_text;
	char			*s_text;
	char			*w_text;
	char			*e_text;
	t_img	img_north;
	t_img	img_south;
	t_img	img_west;
	t_img	img_east;

	int				*floor_color;
	int				*ceiling_color;
}	t_param;

typedef struct s_texture
{
	t_img img;
	int 		texdir; //direction NO, S, EA, WE de la texture
	double		wallx; // valeur où le mur a été touché : coordonnée y si side == 0, coordonnée x si side == 1
	int		texx; // coordonnée x de la texture
	int		texy; // coordonée y de la texture
	double		step; // indique de combien augmenter les coordonnées de la texture pour chaque pixel
	double		texpos; // coordonnée de départ
}	t_texture;

typedef	struct s_draw_wall
{
	int	side_color;


	// int	south_color;
	// int	east_color;
	// int	west_color;
	// int	north_color;
}	t_draw_wall;

typedef struct s_raycast_data
{
	double	angle_raycast_start;
	double	angle_raycast_end;
	double	angle_ray;
	double  angle_raycast_rad;
	double	x;
	double	y;
	double	dist;
	double	new_ray_angle_rad;


	int previous_ray_type;

	double dist_x;
	double dist_y;

	int mapx;
	int mapy;
	int side;
	double dist_to_vertical;
        double wall_dist;
        double dist_to_horizontal;
	int stepx;
        int stepy;

	// double first_horizontal_intersection_x;
	// double first_horizontal_intersection_y;

	// double first_vertical_intersection_x;
	// double first_vertical_intersection_y;

	double horizontal_step_x;
	double horizontal_wall_point_x;
	double horizontal_wall_point_y;
	double horizontal_wall_dist;

	double vertical_step_y;
	double vertical_wall_point_x;
	double vertical_wall_point_y;
	double vertical_wall_dist;

	double dist_x_x;
	double dist_x_y;
	double dist_y_x;
	double dist_y_y;

}	t_raycast_data;

typedef struct s_cub
{
	t_mlx		mlx;
	t_param		params;
	t_player	player;
	t_keys		keys;
	t_minimap	minimap;
	char		**errors;
	double		ray_dir_x;
	double		ray_dir_y;
	t_draw_wall	wall_data;
	t_raycast_data	ray;

}	t_cub;



/*PARSING*/
void	get_params(t_cub *cub, char *filename);
void	*get_param(t_cub *cub, char **file, char *param_name, int param_type);
void	get_map(t_cub *cub, char **file);
void	map_parse(t_cub *cub);
void	error_init(t_cub *cub);
void	error(t_cub *cub, int err, char *arg);

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

#endif