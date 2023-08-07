/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 18:47:12 by egeorgel          #+#    #+#             */
/*   Updated: 2023/08/07 14:30:19 by egeorgel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	angled_movement(t_cub *cub, double radius, bool moving_y, bool *moved)
{
	double	x;
	double	y;

	if (moving_y)
	{
		x = radius * sin(cub->player.angle / 180 * PI);
		y = radius * cos(cub->player.angle / 180 * PI);
	}
	else
	{
		x = radius * sin((cub->player.angle + 90) / 180 * PI);
		y = radius * cos((cub->player.angle + 90) / 180 * PI);
	}
	if (cub->params.map[(int)(round(cub->player.pos.y + y) / 24)]
		[(int)(round(cub->player.pos.x) / 24)] != '1')
		cub->player.pos.y += y;
	if (cub->params.map[(int)(round(cub->player.pos.y) / 24)]
		[(int)(round(cub->player.pos.x + x) / 24)] != '1')
		cub->player.pos.x += x;
	*moved = true;
}

bool	movement(t_cub *cub)
{
	bool	moved;

	moved = false;
	if (cub->keys.r_left)
	{
		cub->player.angle++;
		if (cub->player.angle >= 360)
			cub->player.angle = 0;
		moved = true;
	}
	if (cub->keys.r_right)
	{
		cub->player.angle--;
		if (cub->player.angle < 0)
			cub->player.angle = 359;
		moved = true;
	}
	if (cub->keys.w)
		angled_movement(cub, -1, true, &moved);
	if (cub->keys.a)
		angled_movement(cub, -1, false, &moved);
	if (cub->keys.s)
		angled_movement(cub, 1, true, &moved);
	if (cub->keys.d)
		angled_movement(cub, 1, false, &moved);
	return (moved);
}
