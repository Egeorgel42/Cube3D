/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 20:43:51 by egeorgel          #+#    #+#             */
/*   Updated: 2023/09/18 22:23:25 by egeorgel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//On top are the fonctions for Linux and below for mac.

int	key_press(int keycode, t_cub *cub)
{
	if (keycode == 65307)
		exit(0);
	if (keycode == 0x0057 || keycode == 0x0077)
		cub->keys.w = true;
	if (keycode == 0x0041 || keycode == 0x0061)
		cub->keys.a = true;
	if (keycode == 0x0053 || keycode == 0x0073)
		cub->keys.s = true;
	if (keycode == 0x0044 || keycode == 0x0064)
		cub->keys.d = true;
	if (keycode == 65361)
		cub->keys.r_left = true;
	if (keycode == 65363)
		cub->keys.r_right = true;
	return (0);
}

int	key_release(int keycode, t_cub *cub)
{
	if (keycode == 0x0057 || keycode == 0x0077)
		cub->keys.w = false;
	if (keycode == 0x0041 || keycode == 0x0061)
		cub->keys.a = false;
	if (keycode == 0x0053 || keycode == 0x0073)
		cub->keys.s = false;
	if (keycode == 0x0044 || keycode == 0x0064)
		cub->keys.d = false;
	if (keycode == 65361)
		cub->keys.r_left = false;
	if (keycode == 65363)
		cub->keys.r_right = false;
	return (0);
}
/*
int	key_release(int keycode, t_cub *cub)
{
	if (keycode == 13)
		cub->keys.w = false;
	if (keycode == 0)
		cub->keys.a = false;
	if (keycode == 1)
		cub->keys.s = false;
	if (keycode == 2)
		cub->keys.d = false;
	if (keycode == 123)
		cub->keys.r_left = false;
	if (keycode == 124)
		cub->keys.r_right = false;
	return (0);
}

int	key_press(int keycode, t_cub *cub)
{
	if (keycode == 53)
		exit(0);
	if (keycode == 13)
		cub->keys.w = true;
	if (keycode == 0)
		cub->keys.a = true;
	if (keycode == 1)
		cub->keys.s = true;
	if (keycode == 2)
		cub->keys.d = true;
	if (keycode == 123)
		cub->keys.r_left = true;
	if (keycode == 124)
		cub->keys.r_right = true;
	return (0);
}*/
