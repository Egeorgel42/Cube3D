/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 16:40:02 by egeorgel          #+#    #+#             */
/*   Updated: 2023/09/23 19:04:56 by egeorgel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_map(t_cub *cub, char **file, int *map_end, int *longest_line)
{
	int		i;
	int		j;
	int		map_start;

	i = -1;
	map_start = 0;
	while (file[++i])
	{
		j = 0;
		if ((int)ft_strlen(file[i]) > *longest_line)
			*longest_line = (int)ft_strlen(file[i]);
		while (file[i][j] && (file[i][j] == ' ' || file[i][j] == '\n'))
			j++;
		if (file[i][j] && !map_start)
			map_start = i;
		else if (file[i][j] && *map_end)
			error(cub, TOMANY_PARAM, NULL);
		if (!file[i][j] && map_start && !*map_end)
			*map_end = i - map_start;
	}
	if (!map_start)
		error(cub, NOMAP, NULL);
	if (!*map_end)
		*map_end = i - map_start;
	return (map_start);
}

static char	*get_line(t_cub *cub, char *line, int line_len)
{
	int		i;
	int		j;
	char	*res;

	i = -1;
	j = -1;
	res = malloc(sizeof(char) * (cub->minimap.size_x / 24 + line_len + 3));
	if (!res)
		error(cub, ERRMAX, NULL);
	while (++i <= cub->minimap.size_x / 48)
		res[i] = ' ';
	while (line && line[++j] && line[j] != '\n')
		res[i + j] = line[j];
	while (i + j < line_len + cub->minimap.size_x / 24)
		res[i + j++] = ' ';
	res[i + j] = '\0';
	return (res);
}

static char	**map_cp(t_cub *cub, char **file)
{
	int		i;
	int		j;
	int		k;
	int		line_len;
	char	**map_cp;

	j = 0;
	line_len = 0;
	k = -1;
	i = check_map(cub, file, &j, &line_len);
	get_minimap_size(cub, line_len, j);
	map_cp = malloc(sizeof(char *) * (cub->minimap.size_y / 24 + j + 3));
	if (!map_cp)
		error(cub, ERRMAX, NULL);
	while (++k <= cub->minimap.size_y / 48)
		map_cp[k] = get_line(cub, NULL, line_len);
	while (k <= cub->minimap.size_y / 48 + j)
		map_cp[k++] = get_line(cub, file[i++], line_len);
	while (k <= cub->minimap.size_y / 24 + j)
		map_cp[k++] = get_line(cub, NULL, line_len);
	map_cp[k] = NULL;
	return (map_cp);
}

static void	check_map_was_last(t_cub *cub, char **file)
{
	int	i;

	i = 0;
	while (file[i])
		i++;
	i--;
	while (i > 0 && empty_line(file[i]))
	{
		if (!file[i][0])
			error(cub, PARAM_AFTER_MAP, NULL);
		i--;
	}
}

void	get_map(t_cub *cub, char **file)
{
	check_map_was_last(cub, file);
	cub->params.map = map_cp(cub, file);
	map_parse(cub);
}
