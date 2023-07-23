/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 18:10:42 by egeorgel          #+#    #+#             */
/*   Updated: 2023/07/23 16:44:09 by egeorgel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	get_first_word(t_cub *cub, char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	while (line[i] && line[i] != ' ')
		i++;
	while (line[i] && (line[i] == ' ' || line[i] == '\n'))
		i++;
	if (!line[i])
		error(cub, INVALID_PARAM, NULL);
	return (i);
}

static void	remove_extracted(t_cub *cub, char **line, int i, int j)
{
	char	*begin;
	char	*end;

	begin = ft_substr(*line, 0, i);
	if (!begin)
		error(cub, ERRMAX, NULL);
	end = ft_substr(*line, j, ft_strlen(*line));
	if (!end)
		error(cub, ERRMAX, NULL);
	free(*line);
	*line = ft_strjoinfree(begin, end, true, true);
	if (!line)
		error(cub, ERRMAX, NULL);
}

char	*extract_second_word(t_cub *cub, char **line)
{
	char	*extracted;
	int		i;
	int		j;
	int		d;

	i = get_first_word(cub, *line);
	j = i;
	while ((*line)[j] && (*line)[j] != ' ' && (*line)[j] != '\n')
		j++;
	extracted = ft_substr(*line, i, j - i);
	if (!extracted)
		error(cub, ERRMAX, NULL);
	d = j;
	while ((*line)[d] && ((*line)[d] == ' ' || (*line)[d] == '\n'))
		d++;
	if (!(*line)[d])
		(*line)[0] = '\0';
	else
		remove_extracted(cub, line, i, j);
	return (extracted);
}

long	my_atoi(t_cub *cub, const char *str)
{
	int	i;
	int	res;
	int	sign;

	i = -1;
	res = 0;
	sign = 1;
	if (ft_strcmp(str, "-2147483648"))
		return (INT16_MIN);
	while (str[++i] && ((str[i] >= '0' && str[i] <= '9') || str[i] == ','))
	{
		if (str[i] == ',')
			continue ;
		res *= 10;
		if (res < 0)
			error(cub, ERRINT, NULL);
		res += str[i] - '0';
		if (res < 0)
			error(cub, ERRINT, NULL);
	}
	return (res * sign);
}
