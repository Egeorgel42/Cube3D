/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 16:40:02 by egeorgel          #+#    #+#             */
/*   Updated: 2023/07/27 14:16:19 by egeorgel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_map(t_cub *cub, char **file, int *map_end, unsigned int *longest_line)
{
	int		i;
	int		j;
	int		map_start;

	i = -1;
	map_start = 0;
	while (file[++i])
	{
		j = 0;
		if (ft_strlen(file[i]) > *longest_line)
			*longest_line = ft_strlen(file[i]);
		while (file[i][j] && (file[i][j] == ' ' || file[i][j] == '\n'))
			j++;
		if (file[i][j] && !map_start)
			map_start = i;
		else if (file[i][j] && *map_end)
			error(cub, TOMANY_PARAM, NULL);
		if (!file[i][j] && map_start && !*map_end)
			*map_end = i;
	}
	if (!map_start)
		error(cub, NOMAP, NULL);
	if (!*map_end)
		*map_end = i;
	return (map_start);
}

static char	*get_line(t_cub *cub, char *line, unsigned int line_len)
{
	int		i;
	int		j;
	char	*res;

	i = -1;
	j = -1;
	res = malloc(sizeof(char) * (MAP_SIDE + line_len + 3));
	if (!res)
		error(cub, ERRMAX, NULL);
	while (++i < MAP_SIDE / 2)
		res[i] = ' ';
	while (line && line[++j] && line[j] != '\n')
		res[i + j] = line[j];
	while (j < (int)line_len - 1)
		res[i + j++] = ' ';
	while (i < MAP_SIDE)
		res[i++ + j] = ' ';
	res[i + j] = '\0';
	return (res);
}

static char	**map_cp(t_cub *cub, char **file)
{
	int				i;
	int				j;
	int				k;
	unsigned int	line_len;
	char			**map_cp;

	j = 0;
	line_len = 0;
	k = -1;
	i = check_map(cub, file, &j, &line_len);
	map_cp = malloc(sizeof(char *) * (j - i + MAP_SIDE + 3));
	if (!map_cp)
		error(cub, ERRMAX, NULL);
	while (++k < MAP_SIDE / 2)
		map_cp[k] = get_line(cub, NULL, line_len);
	j -= i;
	while (j-- > 0)
	{
		map_cp[k++] = get_line(cub, file[i], line_len);
		i++;
	}
	while (++j < MAP_SIDE / 2)
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
	}
}

void	get_map(t_cub *cub, char **file)
{
	check_map_was_last(cub, file);
	cub->params.map = map_cp(cub, file);
	map_parse(cub);
}
