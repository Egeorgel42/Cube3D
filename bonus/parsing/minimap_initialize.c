/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_initialize.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ory <ory@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 12:41:09 by ory               #+#    #+#             */
/*   Updated: 2023/09/18 15:48:08 by ory              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_minimap_size(t_cub *cub, int map_x_size, int map_y_size)
{
	int	x;
	int	y;

	x = map_x_size * 24;
	y = map_y_size * 24;
	if (x > 24 * 8)
		x = 24 * 8;
	if (y > 24 * 6)
		y = 24 * 6;
	cub->minimap.size_x = x;
	cub->minimap.size_y = y;
}

void	minimap_initialize(t_cub *cub)
{
	create_image(&cub->mlx, &cub->minimap.img, cub->minimap.size_x,
		cub->minimap.size_y);
}
