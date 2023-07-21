/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_params.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 14:41:08 by egeorgel          #+#    #+#             */
/*   Updated: 2023/07/21 15:47:55 by egeorgel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_params(t_cub *cub, char *filename)
{
	size_t	len;
	int		fd;

	len = ft_strlen(filename);
	if (len < 4 || ft_strnstr(filename, ".cub", len) != filename + len - 4)
		error(cub, ERRFILE);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		error(cub, ERRMAX);
}
