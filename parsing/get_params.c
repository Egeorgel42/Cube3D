/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_params.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ory <ory@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 14:41:08 by egeorgel          #+#    #+#             */
/*   Updated: 2023/09/14 01:21:36 by ory              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_texture_size(t_cub *cub)
{
	if (cub->params.texture_east.img.height != SIZE_OF_CASES || cub->params.texture_east.img.width != SIZE_OF_CASES)
		error(cub, ERR_TEXT_SIZE, " on texture east, texture size must be SIZE_OF_CASES x SIZE_OF_CASES pixels");
	if (cub->params.texture_north.img.height != SIZE_OF_CASES || cub->params.texture_north.img.width != SIZE_OF_CASES)
		error(cub, ERR_TEXT_SIZE, " on texture north, texture size must be SIZE_OF_CASES x SIZE_OF_CASES pixels");
	if (cub->params.texture_south.img.height != SIZE_OF_CASES || cub->params.texture_south.img.width != SIZE_OF_CASES)
		error(cub, ERR_TEXT_SIZE, " on texture south, texture size must be SIZE_OF_CASES x SIZE_OF_CASES pixels");
	if (cub->params.texture_west.img.height != SIZE_OF_CASES || cub->params.texture_west.img.width != SIZE_OF_CASES)
		error(cub, ERR_TEXT_SIZE, " on texture west, texture size must be SIZE_OF_CASES x SIZE_OF_CASES pixels");
}

void	init_texture_addr(t_cub *cub)
{
	cub->params.texture_east.img.addr = mlx_get_data_addr(cub->params.texture_east.img.img, &cub->params.texture_east.img.bits_per_pixel, &cub->params.texture_east.img.line_length, &cub->params.texture_east.img.endian);
	cub->params.texture_north.img.addr = mlx_get_data_addr(cub->params.texture_north.img.img, &cub->params.texture_north.img.bits_per_pixel, &cub->params.texture_north.img.line_length, &cub->params.texture_north.img.endian);
	cub->params.texture_south.img.addr = mlx_get_data_addr(cub->params.texture_south.img.img, &cub->params.texture_south.img.bits_per_pixel, &cub->params.texture_south.img.line_length, &cub->params.texture_south.img.endian);
	cub->params.texture_west.img.addr = mlx_get_data_addr(cub->params.texture_west.img.img, &cub->params.texture_west.img.bits_per_pixel, &cub->params.texture_west.img.line_length, &cub->params.texture_west.img.endian);
}

void	init_texture(t_cub *cub)
{
	if (!(cub->params.texture_east.img.img = mlx_xpm_file_to_image(cub->mlx.mlx, cub->params.e_text, &(cub->params.texture_east.img.width), &(cub->params.texture_east.img.height))))
		error(cub, ERRFILE, " Error texture east");
	if (!(cub->params.texture_north.img.img = mlx_xpm_file_to_image(cub->mlx.mlx, cub->params.n_text, &(cub->params.texture_north.img.width), &(cub->params.texture_north.img.height))))
		error(cub, ERRFILE, "Error texture north");
	if (!(cub->params.texture_south.img.img = mlx_xpm_file_to_image(cub->mlx.mlx, cub->params.s_text, &(cub->params.texture_south.img.width), &(cub->params.texture_south.img.height))))
		error(cub, ERRFILE, "Error texture south");
	if (!(cub->params.texture_west.img.img = mlx_xpm_file_to_image(cub->mlx.mlx, cub->params.w_text, &(cub->params.texture_west.img.width), &(cub->params.texture_west.img.height))))
		error(cub, ERRFILE, "Error texture west");
	init_texture_addr(cub);
	check_texture_size(cub);
}

static int	count_lines(t_cub *cub, char *filename)
{
	int	fd;
	char	*line;
	int	i;

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
