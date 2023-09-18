/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ory <ory@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 17:43:32 by egeorgel          #+#    #+#             */
/*   Updated: 2023/09/18 15:33:58 by ory              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_texture_size(t_cub *cub)
{
	if (cub->params.texture_east.img.height != SIZE_OF_CASES
		|| cub->params.texture_east.img.width != SIZE_OF_CASES)
		error(cub, ERR_TEXT_SIZE,
			" east texture size must be SIZE_OF_CASES x SIZE_OF_CASES");
	if (cub->params.texture_north.img.height != SIZE_OF_CASES
		|| cub->params.texture_north.img.width != SIZE_OF_CASES)
		error(cub, ERR_TEXT_SIZE,
			" north texture size must be SIZE_OF_CASES x SIZE_OF_CASES");
	if (cub->params.texture_south.img.height != SIZE_OF_CASES
		|| cub->params.texture_south.img.width != SIZE_OF_CASES)
		error(cub, ERR_TEXT_SIZE,
			" south texture size must be SIZE_OF_CASES x SIZE_OF_CASES");
	if (cub->params.texture_west.img.height != SIZE_OF_CASES
		|| cub->params.texture_west.img.width != SIZE_OF_CASES)
		error(cub, ERR_TEXT_SIZE,
			" west texture size must be SIZE_OF_CASES x SIZE_OF_CASES");
}

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
	if (!param_name[j] && (!line[i + j] || line[i + j] == ' '))
		return (true);
	return (false);
}

static char	*find_param(t_cub *cub, char **file, char *param_name)
{
	int		i;
	int		j;
	char	*res;

	i = 0;
	while (file[i] && !starts_with(file[i], param_name))
		i++;
	if (!file[i])
		error(cub, MISSING_PARAM, param_name);
	j = i + 1;
	while (file[j] && !starts_with(file[j], param_name))
		j++;
	if (file[j] && i != j)
		error(cub, DOUBLE_PARAM, NULL);
	res = extract_second_word(cub, &file[i]);
	return (res);
}

static void	*convert_param(t_cub *cub, char *res, int param_type)
{
	int	i;
	int	*int_res;

	i = 0;
	while (res[i] && (ft_isdigit(res[i]) || res[i] == ','))
		i++;
	if (res[i] && param_type == STR_PARAM)
		return ((void *)res);
	else if (res[i])
		error(cub, INVALID_PARAM, NULL);
	int_res = malloc(sizeof(int));
	if (!int_res)
		error(cub, ERRMAX, NULL);
	*int_res = get_color(cub, res);
	free(res);
	return ((void *)int_res);
}

void	*get_param(t_cub *cub, char **file, char *param_name, int param_type)
{
	char	*res;

	res = find_param(cub, file, param_name);
	return (convert_param(cub, res, param_type));
}
