/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 18:10:42 by egeorgel          #+#    #+#             */
/*   Updated: 2023/07/23 15:52:27 by egeorgel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*extract_second_word(t_cub *cub, char **line)
{
	char	*begin;
	char	*end;
	char	*extracted;
	int		i;
	int		j;

	i = 0;
	while ((*line)[i] && (*line)[i] == ' ')
		i++;
	while ((*line)[i] && (*line)[i] != ' ')
		i++;
	while ((*line)[i] && ((*line)[i] == ' ' || (*line)[i] == '\n'))
		i++;
	if (!(*line)[i])
		error(cub, INVALID_PARAM, NULL);
	j = i;
	while ((*line)[j] && (*line)[j] != ' ' && (*line)[j] != '\n')
		j++;
	begin = ft_substr(*line, 0, i);
	end = ft_substr(*line, j, ft_strlen(*line));
	extracted = ft_substr(*line, i, j - i);
	free(*line);
	*line = ft_strjoinfree(begin, end, true, true);
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
