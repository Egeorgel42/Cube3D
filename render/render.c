/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ory <ory@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 20:18:44 by ory               #+#    #+#             */
/*   Updated: 2023/09/18 16:20:16 by ory              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_texture(t_cub *cub)
{
	if (cub->wall_data.side_color == 1 && cub->ray.ray_dir_y < 0)
	{
		cub->params.texture = &cub->params.texture_north;
		cub->params.texture->wallx = (int)cub->ray.x % SIZE_OF_CASES;
	}
	else if (cub->wall_data.side_color == 1 && cub->ray.ray_dir_y > 0)
	{
		cub->params.texture = &cub->params.texture_south;
		cub->params.texture->wallx = SIZE_OF_CASES
			- (int)cub->ray.x % SIZE_OF_CASES;
	}
	if (cub->wall_data.side_color == 0 && cub->ray.ray_dir_x < 0)
	{
		cub->params.texture = &cub->params.texture_east;
		cub->params.texture->wallx = SIZE_OF_CASES
			- (int)cub->ray.y % SIZE_OF_CASES;
	}
	else if (cub->wall_data.side_color == 0 && cub->ray.ray_dir_x > 0)
	{
		cub->params.texture = &cub->params.texture_west;
		cub->params.texture->wallx = (int)cub->ray.y % SIZE_OF_CASES;
	}
}

int	cast_ray_horizontal(t_cub *cub)
{
	cub->ray.mapx += cub->ray.stepx;
	cub->ray.x += cub->ray.ray_dir_x * cub->ray.dist_x;
	cub->ray.y += cub->ray.ray_dir_y * cub->ray.dist_x;
	if (cub->params.map[cub->ray.mapy][cub->ray.mapx] == '1')
	{
		cub->ray.wall_dist = cub->ray.dist_x;
		cub->wall_data.side_color = 0;
		return (true);
	}
	cub->ray.dist_to_vertical = cub->ray.dist_to_vertical
		+ (double)SIZE_OF_CASES;
	cub->ray.dist_x = fabs(cub->ray.dist_to_vertical
			/ cub->ray.ray_dir_x);
	return (false);
}

int	cast_ray_vertical(t_cub *cub)
{
	cub->ray.mapy += cub->ray.stepy;
	cub->ray.x += cub->ray.ray_dir_x * cub->ray.dist_y;
	cub->ray.y += cub->ray.ray_dir_y * cub->ray.dist_y;
	if (cub->params.map[cub->ray.mapy][cub->ray.mapx] == '1')
	{
		cub->ray.wall_dist = cub->ray.dist_y;
		cub->wall_data.side_color = 1;
		return (true);
	}
	cub->ray.dist_to_horizontal = cub->ray.dist_to_horizontal
		+ (double)SIZE_OF_CASES;
	cub->ray.dist_y = fabs(cub->ray.dist_to_horizontal
			/ cub->ray.ray_dir_y);
	return (false);
}

void	find_dist(t_cub *cub)
{
	while (cub->ray.x >= 0 && cub->ray.y >= 0)
	{
		cub->ray.x = cub->player.pos.x;
		cub->ray.y = cub->player.pos.y;
		cub->ray.wall_dist = 0;
		if ((cub->ray.dist_x < cub->ray.dist_y)
			|| fabs(cub->ray.ray_dir_y) == 0)
			if (cast_ray_horizontal(cub))
				break ;
		cub->ray.x = cub->player.pos.x;
		cub->ray.y = cub->player.pos.y;
		cub->ray.wall_dist = 0;
		if (cub->ray.dist_y < cub->ray.dist_x)
			if (cast_ray_vertical(cub))
				break ;
	}
}

void	render(t_cub *cub)
{
	cub->ray.print_x = 0;
	cub->player.rad_angle = cub->player.angle * cub->degre_to_rad;
	cub->ray.angle_raycast_rad = cub->player.rad_angle
		+ (FOV * cub->degre_to_rad / 2);
	while (cub->ray.print_x < WIN_X)
	{
		ray_var_init(cub);
		find_dist(cub);
		draw_wall(cub->ray.wall_dist, cub);
		cub->ray.angle_raycast_rad -= cub->decrease_angle;
		cub->ray.print_x++;
	}
}
