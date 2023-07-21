/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 17:43:32 by egeorgel          #+#    #+#             */
/*   Updated: 2023/07/21 18:30:55 by egeorgel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	starts_with(char *line, char *param_name)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (line[i] && line[i] == ' ')
		i++;
	while (line[i + j] && param_name[j] && line[i + j] == param_name[j])
		j++;
	if (!param_name[j])
		return (true);
	return (false);
}

static char	*find_param(t_cub *cub, char **file, char *param_name)
{
	int	i;

	i = 0;
	while (file[i] && !starts_with(file[i], param_name))
		i++;
	if (!file[i])
		error(cub, MISSING_PARAM, param_name);
	rem_first_word(&file[i]);
	if (!file[i])
		error(cub, INVALID_PARAM, NULL);
	return (file[i]);
}

void	get_param(t_cub *cub, char **file, char *param_name, void *param)
{
	char	*line;

	line = find_param(cub, file, param_name);
	if (param || !param)
		param = line;
	ft_printf("%s\n", line);
}
