/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_params.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ory <ory@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 14:41:08 by egeorgel          #+#    #+#             */
/*   Updated: 2023/07/25 15:40:10 by ory              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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
	cub->params.res_x = (int *)get_param(cub, file, "R");
	cub->params.res_y = (int *)get_param(cub, file, "R");
	cub->params.n_text = (char *)get_param(cub, file, "NO");
	cub->params.s_text = (char *)get_param(cub, file, "SO");
	cub->params.w_text = (char *)get_param(cub, file, "WE");
	cub->params.e_text = (char *)get_param(cub, file, "EA");
	cub->params.sprite_text = (char *)get_param(cub, file, "S");
	cub->params.floor_color = (int *)get_param(cub, file, "F");
	cub->params.ceiling_color = (int *)get_param(cub, file, "C");
	//get_map(cub, file);
	freetab((void **)file);
}
