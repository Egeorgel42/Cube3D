/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ory <ory@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 23:10:47 by ory               #+#    #+#             */
/*   Updated: 2023/08/25 14:54:38 by ory              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool    find_wall(t_cub *cub, int x, int y)
{
        int i = x / SIZE_OF_CASES;
        int j = y / SIZE_OF_CASES;
        if (cub->params.map[j][i] == '1')
                return (true);
        else
                return (false);
        
}

void render(t_cub *cub)
{
        t_raycast_data ray;
        ray.angle_raycast_start = cub->player.angle + FOV / 2;
        if (ray.angle_raycast_start >= 360)
                ray.angle_raycast_start = fmod(ray.angle_raycast_start, 360);
        ray.angle_raycast_end = ray.angle_raycast_start - FOV;
        ray.angle_ray = (double)FOV / (double)WIN_X;

        ray.dist = 0;
        while(ray.angle_raycast_start > ray.angle_raycast_end)
        {
                cub->ray_dir_x = cos(ray.angle_raycast_start * (PI / 180));
                cub->ray_dir_y = -sin(ray.angle_raycast_start * (PI / 180));
                ray.x = cub->player.pos.x;
                ray.y = cub->player.pos.y;
                while(!find_wall(cub, ray.x, ray.y))
                {

                        ray.x = ray.x + cub->ray_dir_x;
                        ray.y = ray.y + cub->ray_dir_y;
                        mlx_pixel_put(cub->mlx.mlx, cub->mlx.mlx_win, (int)ray.x, (int)ray.y, 0xE6);
                }
                ray.dist = sqrt(pow(ray.x - cub->player.pos.x, 2) + pow(ray.y - cub->player.pos.y, 2));
                //draw_wall(ray.x, ray.dist, cub);
                ray.angle_raycast_start = ray.angle_raycast_start - ray.angle_ray;
        }
}