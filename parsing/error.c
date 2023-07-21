/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 15:13:05 by egeorgel          #+#    #+#             */
/*   Updated: 2023/07/21 23:48:42 by egeorgel         ###   ########.fr       */
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
	cub->errors = malloc(sizeof(char *) * (ERRMAX + 1));
	cub->errors[ERRFILE] = ft_strdup("Invalid file type");
	cub->errors[MISSING_PARAM] = ft_strdup("file is missing the parameter ");
	cub->errors[INVALID_PARAM] = ft_strdup("parameter is invalid");
	cub->errors[ERRINT] = ft_strdup("parameter is longer than a int");
	cub->errors[ERRMAX] = NULL;
}
