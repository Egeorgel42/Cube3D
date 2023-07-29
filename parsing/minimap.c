/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 14:51:32 by egeorgel          #+#    #+#             */
/*   Updated: 2023/07/28 17:32:19 by egeorgel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	create_minimap(t_cub *cub)
{
	int	i;
	int	j;

	i = -1;
	create_image(&cub->mlx, &cub->minimap.img, cub->minimap.size_x,
		cub->minimap.size_y);
	while (++i < cub->minimap.size_y)
	{
		j = -1;
		while (++j < cub->minimap.size_x)
			pixel_to_img(&cub->minimap.img, j, i, 0x00FF0000);
	}
}

static void	get_minimap_size(t_cub *cub)
{
	int	x;
	int	y;

	x = line_size(cub->params.map);
	y = map_size(cub->params.map);
}

void	minimap(t_cub *cub)
{
	
	create_minimap(cub);
}
