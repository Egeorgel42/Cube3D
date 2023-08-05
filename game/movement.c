/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 18:47:12 by egeorgel          #+#    #+#             */
/*   Updated: 2023/08/05 22:18:32 by egeorgel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	angled_movement(t_cub *cub, double radius, bool moving_y, bool *moved)
{
	if (moving_y)
	{
		cub->player.pos.x += radius * sin(cub->player.angle / 180 * PI);
		cub->player.pos.y += radius * cos(cub->player.angle / 180 * PI);
	}
	else
	{
		cub->player.pos.x += radius * sin((cub->player.angle + 90) / 180 * PI);
		cub->player.pos.y += radius * cos((cub->player.angle + 90) / 180 * PI);
	}
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
