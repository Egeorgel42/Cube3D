/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 15:13:05 by egeorgel          #+#    #+#             */
/*   Updated: 2023/07/21 16:31:13 by egeorgel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	error(t_cub *cub, int err)
{
	ft_printf("Error\n");
	if (err == ERRMAX)
		perror(NULL);
	else
		ft_printf("%s\n", cub->errors[err]);
	exit(1);
}

void	error_init(t_cub *cub)
{
	cub->errors = malloc(sizeof(char *) * (ERRMAX + 1));
	cub->errors[ERRFILE] = ft_strdup("Invalid file type");
	cub->errors[ERRMAX] = NULL;
}
