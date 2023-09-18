/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 18:10:42 by egeorgel          #+#    #+#             */
/*   Updated: 2023/07/28 16:32:12 by egeorgel         ###   ########.fr       */
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

char	*extract_second_word(t_cub *cub, char **line)
{
	char	*extracted;
	int		i;
	int		j;

	i = get_first_word(cub, *line);
	j = i;
	while ((*line)[j] && (*line)[j] != ' ' && (*line)[j] != '\n')
		j++;
	extracted = ft_substr(*line, i, j - i);
	if (!extracted)
		error(cub, ERRMAX, NULL);
	(*line)[0] = '\0';
	return (extracted);
}

static int	get_color_subparam(t_cub *cub, const char *str, int *i)
{
	int	color;

	color = 0;
	while (str[*i] && str[*i] >= '0' && str[*i] <= '9')
	{
		color *= 10;
		color += str[*i] - '0';
		if (color > 255)
			error(cub, ERRCOLOR, NULL);
		(*i)++;
	}
	return (color);
}

int	get_color(t_cub *cub, const char *str)
{
	int	i;
	int	res;
	int	exponent;

	i = 0;
	res = 0;
	exponent = 16;
	if (str[i] && str[i] == ',')
		error(cub, INVALID_PARAM, NULL);
	while (str[i] && ((str[i] >= '0' && str[i] <= '9') || str[i] == ','))
	{
		if (str[i] == ',' && (!str[i + 1] || str[i + 1] == ','
				|| !(str[i] >= '0' && str[i] <= '9')))
			error(cub, INVALID_PARAM, NULL);
		res += get_color_subparam(cub, str, &i) << exponent;
		exponent -= 8;
		if (str[i] && str[i] == ',' && exponent != -8)
			i++;
	}
	if (exponent != -8 || str[i])
		error(cub, INVALID_PARAM, NULL);
	return (res);
}
