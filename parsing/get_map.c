/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ory <ory@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 16:40:02 by egeorgel          #+#    #+#             */
/*   Updated: 2023/07/26 16:07:59 by ory              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	check_map(t_cub *cub, char **file, int *map_end, unsigned int *longest_line)
{
	int		i;
	int		j;
	int		map_start;

	i = 0;
	map_start = 0;
	while (file[i])
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
		i++;
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
	res = malloc(sizeof(char) * (*cub->params.res_x + line_len + 5));
	if (!res)
		error(cub, ERRMAX, NULL);
	while (++i <= *cub->params.res_x / 2)
		res[i] = ' ';
	while (line && line[++j] && line[j] != '\n')
		res[i + j] = line[j];
	while (j < (int)line_len - 1)
		res[i + j++] = ' ';
	while (i <= *cub->params.res_x)
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
	map_cp = malloc(sizeof(char *) * (j - i + *cub->params.res_y + 2));
	if (!map_cp)
		error(cub, ERRMAX, NULL);
	while (++k <= *cub->params.res_x / 2)
		map_cp[k] = get_line(cub, NULL, line_len);
	j -= i;
	while (j-- > 0)
	{
		map_cp[k++] = get_line(cub, file[i], line_len);
		i++;
	}
	while (++j <= *cub->params.res_x / 2)
		map_cp[k++] = get_line(cub, NULL, line_len);
	map_cp[k] = NULL;
	return (map_cp);
}

void	get_map(t_cub *cub, char **file)
{
	cub->params.map = map_cp(cub, file);
}
