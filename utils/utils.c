/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 12:58:00 by egeorgel          #+#    #+#             */
/*   Updated: 2023/07/28 17:30:00 by egeorgel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	freetab(void **tab)
{
	int	i;

	i = -1;
	while (tab[++i])
		free(tab[i]);
	free(tab);
}

bool	empty_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!ft_strchr(" \n", line[i]))
			return (false);
	}
	return (true);
}

int	line_size(char *line)
{
	int	i;
	int	j;

	j = 0;
	i = -1;
	while (line[++i])
		if (line[i] != ' ' && line != '\n')
			j++;
	return (j);
}

int	map_size(char **map)
{
	int	i;
	int	j;
	int	k;

	i = -1;
	k = 0;
	while (map[++i])
	{
		j = 0;
		while (map[i][j] && (map[i][j] == ' ' || map[i][j] == '\n'))
			j++;
		if (map[i][j])
			k++;
	}
	return (k);
}
