/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ory <ory@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 18:47:12 by egeorgel          #+#    #+#             */
/*   Updated: 2023/09/14 12:34:36 by ory              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	angled_movement(t_cub *cub, double angle)
{
	double	x;
	double	y;
	double	dir_x;
	double	dir_y;

	dir_x = cos((cub->player.angle + angle) / 180 * PI);
	dir_y = -sin((cub->player.angle + angle) / 180 * PI);
	cub->player.pos.dist_to_wall_limit = 10;
	x = cub->player.pos.x + MV_SCALING * dir_x;
 	y = cub->player.pos.y + MV_SCALING * dir_y;
	cub->player.pos.check_x = x + dir_x * cub->player.pos.dist_to_wall_limit;
	cub->player.pos.check_y = y + dir_y * cub->player.pos.dist_to_wall_limit;
	if (cub->params.map[(int)(cub->player.pos.check_y/ SIZE_OF_CASES)][(int)(cub->player.pos.x / SIZE_OF_CASES)] != '1')
		cub->player.pos.y = y;
	if (cub->params.map[(int)(cub->player.pos.y/ SIZE_OF_CASES)][(int)(cub->player.pos.check_x / SIZE_OF_CASES)] != '1')
		cub->player.pos.x = x;
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
		return (315);
	else if (cub->keys.d && cub->keys.s)
		return (225);
	else if (cub->keys.a && cub->keys.s)
		return (135);
	else if (cub->keys.a && cub->keys.w)
		return (45);
	else if (cub->keys.w)
		return (0);
	else if (cub->keys.a)
		return (90);
	else if (cub->keys.s)
		return (180);
	else if (cub->keys.d)
		return (-90);
	else
		return (-1);
}

bool	movement(t_cub *cub)
{
	double	angle;

	angle = 0;
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
		return (true);
	return (false);
}
