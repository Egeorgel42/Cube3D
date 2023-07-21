/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_params.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 14:41:08 by egeorgel          #+#    #+#             */
/*   Updated: 2023/07/21 18:38:23 by egeorgel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

static void	get_file(t_cub *cub, char ***file, char *filename)
{
	int	fd;
	int	i;

	i = 0;
	*file = malloc(sizeof(char *) * (count_lines(cub, filename) + 1));
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		error(cub, ERRMAX, NULL);
	(*file)[i] = get_next_line(fd);
	while ((*file)[i])
	{
		i++;
		(*file)[i] = get_next_line(fd);
	}
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
	get_file(cub, &file, filename);
	get_param(cub, file, "R", &cub->params.res_x);
	get_param(cub, file, "R", &cub->params.res_y);
}
