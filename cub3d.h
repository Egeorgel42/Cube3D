/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 11:44:30 by egeorgel          #+#    #+#             */
/*   Updated: 2023/07/23 15:42:26 by egeorgel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <mlx.h>
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <limits.h>
# include "libft/libft.h"

/*ERRORS*/

typedef enum e_err
{
	ERRFILE,
	MISSING_PARAM,
	INVALID_PARAM,
	DOUBLE_PARAM,
	ERRINT,
	ERRMAX,
}	t_err;

/*STRUCT*/

typedef struct s_mlx
{
	void	*mlx;
	void	*mlx_win;
}	t_mlx;

typedef struct s_param
{
	char	**map;
	int		*res_x;
	int		*res_y;
	char	*n_text;
	char	*s_text;
	char	*w_text;
	char	*e_text;
	char	*sprite_text;
	int		*floor_color;
	int		*ceiling_color;
}	t_param;

typedef struct s_cub
{
	t_mlx	mlx;
	t_param	params;
	char	**errors;
}	t_cub;

/*PARSING*/
void	get_params(t_cub *cub, char *filename);
void	*get_param(t_cub *cub, char **file, char *param_name);
void	error_init(t_cub *cub);
void	error(t_cub *cub, int err, char *arg);

/*UTILS*/
char	*extract_second_word(t_cub *cub, char **line);
long	my_atoi(t_cub *cub, const char *str);
void	freetab(void **tab);

#endif