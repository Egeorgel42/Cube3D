/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 10:58:54 by egeorgel          #+#    #+#             */
/*   Updated: 2023/09/11 16:18:39 by egeorgel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// static void	get_player(t_cub *cub, char **map, int i, int j)
// {
// 	cub->player.pos.y = i * SIZE_OF_CASES + SIZE_OF_CASES / 2;
// 	cub->player.pos.x = j * SIZE_OF_CASES + SIZE_OF_CASES / 2;
// 	if (map[i][j] == 'N')
// 		cub->player.angle = 0;
// 	else if (map[i][j] == 'W')
// 		cub->player.angle = 90;
// 	else if (map[i][j] == 'S')
// 		cub->player.angle = 180;
// 	else
// 		cub->player.angle = 270;
// }

static void	get_player(t_cub *cub, char **map, int i, int j)
{
	cub->player.pos.y = i * SIZE_OF_CASES + SIZE_OF_CASES / 2;
	cub->player.pos.x = j * SIZE_OF_CASES + SIZE_OF_CASES / 2;
	if (map[i][j] == 'N')
		cub->player.angle = 90;
	else if (map[i][j] == 'W')
		cub->player.angle = 180;
	else if (map[i][j] == 'S')
		cub->player.angle = 270;
	else
		cub->player.angle = 0;
}

static void	check_map_space(t_cub *cub, char **map, int i)
{
	int		j;
	
	j = 0;
	while (map[i][j] && map[i][j] == ' ')
	{
		j++;
	}
	while (map[i][j] && map[i][j] != ' ')
	{
		j++;
	}
	while (map[i][j] && map[i][j] == ' ')
	{
		j++;
	}
	if (map[i][j])
		error(cub, MAPSPACE, NULL);
}

static void	check_element(t_cub *cub, char **map, int i, int j)
{
	if (map[i][j] == '0' && ((!map[i][j + 1] || map[i][j + 1] == ' ')
		|| map[i][j - 1] == ' ' || map[i - 1][j] == ' '
		|| (!map[i + 1][j] || map[i + 1][j] == ' ')))
	{
		error(cub, MAPHOLE, NULL);
	}
	if (!ft_strchr("10EWNS ", map[i][j]))
	{
		error(cub, INVALID_MAP_CHARACTER, NULL);
	}
	if (!cub->player.pos.x && !cub->player.pos.y
		&& ft_strchr("EWNS", map[i][j]))
	{
		get_player(cub, map, i, j);
	}
	else if (ft_strchr("EWNS", map[i][j]))
		error(cub, MULTIPLE_PLAYERS, NULL);
}

static void	map_parcour(t_cub *cub, char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			check_element(cub, map, i, j);
			j++;
		}
		check_map_space(cub, map, i);
		i++;
	}
	if (!cub->player.pos.x && !cub->player.pos.y)
		error(cub, NOPLAYER, NULL);
}

void	map_parse(t_cub *cub)
{
	char	**map;

	map = cub->params.map;
	map_parcour(cub, map);
}
