/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_initialize.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 14:51:32 by egeorgel          #+#    #+#             */
/*   Updated: 2023/08/03 16:55:00 by egeorgel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	get_minimap_size(t_cub *cub)
{
	int	x;
	int	y;

	x = line_size(cub->params.map) * 24;
	y = map_size(cub->params.map) * 24;
	if (x > 24 * 17)
		x = 24 * 17;
	if (y > 24 * 10)
		y = 24 * 10;
	cub->minimap.size_x = x;
	cub->minimap.size_y = y;
}

void	minimap_initialize(t_cub *cub)
{
	get_minimap_size(cub);
	create_image(&cub->mlx, &cub->minimap.img, cub->minimap.size_x,
		cub->minimap.size_y);
}
