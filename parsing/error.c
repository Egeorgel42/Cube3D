/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ory <ory@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 15:13:05 by egeorgel          #+#    #+#             */
/*   Updated: 2023/09/13 15:00:04 by ory              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	error(t_cub *cub, int err, char *arg)
{
	ft_printf("Error\n");
	if (err == ERRMAX)
		perror(NULL);
	else
	{
		ft_printf("%s", cub->errors[err]);
		if (arg)
			ft_printf("%s", arg);
		ft_printf("\n");
	}
	exit(1);
}

void	error_init(t_cub *cub)
{
	cub->i_error = -1;
	cub->errors = malloc(sizeof(char *) * (ERRMAX + 1));
	if (!cub->errors)
		error(cub, ERRMAX, NULL);
	cub->errors[ERRMLX] = ft_strdup("MLX init error");
	cub->errors[ERRFILE] = ft_strdup("Invalid file type");
	cub->errors[MISSING_PARAM] = ft_strdup("file is missing the parameter ");
	cub->errors[INVALID_PARAM] = ft_strdup("parameter is invalid");
	cub->errors[DOUBLE_PARAM] = ft_strdup("parameter is declared two times");
	cub->errors[TOMANY_PARAM]
		= ft_strdup("too many parameters, or seperated map");
	cub->errors[PARAM_AFTER_MAP] = ft_strdup("parameter after map");
	cub->errors[NOMAP] = ft_strdup("no map found");
	cub->errors[NOPLAYER] = ft_strdup("no player found");
	cub->errors[MULTIPLE_PLAYERS] = ft_strdup("multiple players found");
	cub->errors[INVALID_MAP_CHARACTER] = ft_strdup("invalid map character");
	cub->errors[MAPHOLE] = ft_strdup("map is not fully surrounded by walls");
	cub->errors[ERRCOLOR] = ft_strdup("color parameter is bigger than 255");
	cub->errors[NB_ARG] = ft_strdup("less or more than 1 argument to ./cub3D");
	cub->errors[ERR_TEXT_FILE] = ft_strdup("impossible to get texture file");
	cub->errors[ERR_TEXT_SIZE] = ft_strdup("texture size error");
	cub->errors[ERRMAX] = NULL;
	while (++cub->i_error < ERRMAX)
		if (!cub->errors[cub->i_error])
			error(cub, ERRMAX, NULL);
}
