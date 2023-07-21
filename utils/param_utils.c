/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 18:10:42 by egeorgel          #+#    #+#             */
/*   Updated: 2023/07/21 18:39:58 by egeorgel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rem_first_word(char **line)
{
	char	*buf;
	int		i;

	i = 0;
	while ((*line)[i] && ((*line)[i] == ' ' || (*line)[i] == ','))
		i++;
	while ((*line)[i] && !((*line)[i] == ' ' || (*line)[i] == ','))
		i++;
	while ((*line)[i] && ((*line)[i] == ' ' || (*line)[i] == ','))
		i++;
	if (!(*line)[i])
	{
		free(*line);
		*line = NULL;
	}
	else
	{
		buf = ft_substr(*line, i, ft_strlen(*line));
		free(*line);
		*line = buf;
	}
}
