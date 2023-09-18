/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_params.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ory <ory@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 14:41:08 by egeorgel          #+#    #+#             */
/*   Updated: 2023/09/18 15:50:09 by ory              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_texture_addr(t_cub *cub)
{
	cub->params.texture_east.img.addr = mlx_get_data_addr
		(cub->params.texture_east.img.img,
			&cub->params.texture_east.img.bits_per_pixel,
			&cub->params.texture_east.img.line_length,
			&cub->params.texture_east.img.endian);
	cub->params.texture_north.img.addr = mlx_get_data_addr
		(cub->params.texture_north.img.img,
			&cub->params.texture_north.img.bits_per_pixel,
			&cub->params.texture_north.img.line_length,
			&cub->params.texture_north.img.endian);
	cub->params.texture_south.img.addr = mlx_get_data_addr
		(cub->params.texture_south.img.img,
			&cub->params.texture_south.img.bits_per_pixel,
			&cub->params.texture_south.img.line_length,
			&cub->params.texture_south.img.endian);
	cub->params.texture_west.img.addr = mlx_get_data_addr
		(cub->params.texture_west.img.img,
			&cub->params.texture_west.img.bits_per_pixel,
			&cub->params.texture_west.img.line_length,
			&cub->params.texture_west.img.endian);
}

void	init_texture(t_cub *cub)
{
	load_texture(cub, &(cub->params.texture_east),
		cub->params.e_text, " east");
	load_texture(cub, &(cub->params.texture_north),
		cub->params.n_text, " north");
	load_texture(cub, &(cub->params.texture_south),
		cub->params.s_text, " south");
	load_texture(cub, &(cub->params.texture_west),
		cub->params.w_text, " west");
	init_texture_addr(cub);
	check_texture_size(cub);
}

static int	count_lines(t_cub *cub, char *filename)
{
	int		fd;
	char	*line;
	int		i;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		error(cub, ERRMAX, NULL);
	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
		i++;
	}
	close(fd);
	return (i);
}

static char	**get_file(t_cub *cub, char *filename)
{
	char	**file;
	int		fd;
	int		i;

	i = 0;
	file = malloc(sizeof(char *) * (count_lines(cub, filename) + 1));
	if (!file)
		error(cub, ERRMAX, NULL);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		error(cub, ERRMAX, NULL);
	file[i] = get_next_line(fd);
	while (file[i])
	{
		i++;
		file[i] = get_next_line(fd);
	}
	return (file);
}

void	get_params(t_cub *cub, char *filename)
{
	char	**file;
	char	*filename_end;
	size_t	len;

	file = NULL;
	len = ft_strlen(filename);
	if (len < 4)
		error(cub, ERRFILE, NULL);
	filename_end = ft_substr(filename, len - 4, 4);
	if (!ft_strcmp(filename_end, ".cub"))
		error(cub, ERRFILE, NULL);
	free(filename_end);
	file = get_file(cub, filename);
	cub->params.n_text = (char *)get_param(cub, file, "NO", STR_PARAM);
	cub->params.s_text = (char *)get_param(cub, file, "SO", STR_PARAM);
	cub->params.w_text = (char *)get_param(cub, file, "WE", STR_PARAM);
	cub->params.e_text = (char *)get_param(cub, file, "EA", STR_PARAM);
	cub->params.floor_color = (int *)get_param(cub, file, "F", INT_PARAM);
	cub->params.ceiling_color = (int *)get_param(cub, file, "C", INT_PARAM);
	get_map(cub, file);
	freetab((void **)file);
	init_texture(cub);
}
