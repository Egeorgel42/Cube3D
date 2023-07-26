/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 10:58:54 by egeorgel          #+#    #+#             */
/*   Updated: 2023/07/26 18:24:17 by egeorgel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	check_element(t_cub *cub, char **map, int i, int j)
{
	if (map[i][j] == '0' && ((!map[i][j + 1] || map[i][j + 1] == ' ')
		|| map[i][j - 1] == ' ' || map[i - 1][j] == ' '
		|| (!map[i + 1][j] || map[i + 1][j] == ' ')))
	{
		error(cub, MAPHOLE, NULL);
	}
	if (!ft_strchr("10EWNS ", map[i][j]))
		error(cub, INVALID_MAP_CHARACTER, NULL);
	if (!cub->params.player_pos.x && !cub->params.player_pos.y
		&& ft_strchr("EWNS", map[i][j]))
	{
		cub->params.player_pos.y = i;
		cub->params.player_pos.x = j;
	}
	else if (ft_strchr("EWNS", map[i][j]))
		error(cub, MULTIPLE_PLAYERS, NULL);
}

static void	map_parcour(t_cub *cub, char **map)
{
	int	i;
	int	j;

	i = MAP_SIDE / 2;
	while (map[i])
	{
		j = MAP_SIDE / 2;
		while (map[i][j])
		{
			check_element(cub, map, i, j);
			j++;
		}
		i++;
	}
	if (!cub->params.player_pos.x && !cub->params.player_pos.y)
		error(cub, NOPLAYER, NULL);
}

void	map_parse(t_cub *cub)
{
	char	**map;

	map = cub->params.map;
	map_parcour(cub, map);
}
