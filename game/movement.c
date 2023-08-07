/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 18:47:12 by egeorgel          #+#    #+#             */
/*   Updated: 2023/08/07 22:50:07 by egeorgel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	angled_movement(t_cub *cub, double angle)
{
	double	x;
	double	y;

	x = sin((cub->player.angle + angle) / 180 * PI);
	y = cos((cub->player.angle + angle) / 180 * PI);
	if (cub->params.map[(int)(round(cub->player.pos.y - y) / 24)]
		[(int)(round(cub->player.pos.x) / 24)] != '1')
		cub->player.pos.y -= y;
	if (cub->params.map[(int)(round(cub->player.pos.y) / 24)]
		[(int)(round(cub->player.pos.x - x) / 24)] != '1')
		cub->player.pos.x -= x;
}

static double	addup_movement(t_cub *cub)
{
	if (cub->keys.w && cub->keys.a && cub->keys.s && cub->keys.d)
		return (-1);
	else if (cub->keys.a && cub->keys.d && cub->keys.w)
		return (0);
	else if (cub->keys.w && cub->keys.s && cub->keys.a)
		return (90);
	else if (cub->keys.a && cub->keys.d && cub->keys.s)
		return (180);
	else if (cub->keys.w && cub->keys.s && cub->keys.d)
		return (270);
	else if ((cub->keys.s && cub->keys.w) || (cub->keys.a && cub->keys.d))
		return (-1);
	else if (cub->keys.d && cub->keys.w)
		return (45);
	else if (cub->keys.d && cub->keys.s)
		return (225);
	else if (cub->keys.a && cub->keys.s)
		return (135);
	else if (cub->keys.a && cub->keys.w)
		return (315);
	else if (cub->keys.w)
		return (0);
	else if (cub->keys.a)
		return (90);
	else if (cub->keys.s)
		return (180);
	else if (cub->keys.d)
		return (270);
	else
		return (-1);
}

bool	movement(t_cub *cub)
{
	bool	moved;
	double	angle;

	angle = 0;
	moved = false;
	if (cub->keys.r_left)
	{
		cub->player.angle++;
		if (cub->player.angle >= 360)
			cub->player.angle = 0;
	}
	if (cub->keys.r_right)
	{
		cub->player.angle--;
		if (cub->player.angle < 0)
			cub->player.angle = 359;
	}
	angle = addup_movement(cub);
	if (angle != -1)
		angled_movement(cub, angle);
	if (angle != -1 || cub->keys.r_left || cub->keys.r_right)
		moved = true;
	return (moved);
}
