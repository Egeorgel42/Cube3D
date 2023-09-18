/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ory <ory@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 20:18:03 by ory               #+#    #+#             */
/*   Updated: 2023/09/18 16:08:34 by ory              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_cub *cub, int x, int y, int color)
{
	char	*dst;

	dst = cub->view.addr + (y * cub->view.line_length
			+ x * (cub->view.bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	pixel_to_image(t_cub *cub)
{
	char	*pixel;
	int		color;

	pixel = cub->params.texture->img.addr
		+ ((int)cub->params.texture->texy
			* cub->params.texture->img.line_length
			+ (int)cub->params.texture->texx
			* (cub->params.texture->img.bits_per_pixel / 8));
	color = *(int *)pixel;
	pixel_to_img(&cub->view, cub->ray.print_x, cub->ray.draw_y, color);
}

void	draw_floor(t_cub *cub)
{
	int	y;

	y = cub->ray.draw_y;
	while (y < cub->win_y)
	{
		my_mlx_pixel_put(cub, cub->ray.print_x, y, *cub->params.floor_color);
		y++;
	}
}

void	draw_sky(t_cub *cub)
{
	int	y;

	y = cub->wall_data.wall_top - 1;
	while (y > -1)
	{
		my_mlx_pixel_put(cub, cub->ray.print_x, y, *cub->params.ceiling_color);
		y--;
	}
}

void	draw_wall(double ray_dist, t_cub *cub)
{
	init_wall(cub, ray_dist);
	set_texture(cub);
	cub->params.texture->texx = cub->params.texture->wallx;
	cub->params.texture->texy = 0;
	if (cub->wall_data.wall_height >= cub->win_y)
		cub->params.texture->texy
			= (((cub->wall_data.wall_height - cub->win_y) / 2)
				/ cub->wall_data.wall_height) * SIZE_OF_CASES;
	while (cub->ray.draw_y < (int)cub->wall_data.wall_bottom
		&& cub->ray.draw_y < cub->win_y
		&& cub->params.texture->texy < cub->params.texture->img.height - 1)
	{
		pixel_to_image(cub);
		cub->ray.draw_y++;
		cub->params.texture->texy
			+= cub->params.texture->img.height
			/ (double)cub->wall_data.wall_height;
	}
	draw_floor(cub);
	draw_sky(cub);
}
