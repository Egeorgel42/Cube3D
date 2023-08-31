/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ory <ory@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 23:10:47 by ory               #+#    #+#             */
/*   Updated: 2023/08/31 18:17:26 by ory              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool    find_wall(t_cub *cub, double x, double y)
{
        int i = x / (double)SIZE_OF_CASES;
        int j = y / (double)SIZE_OF_CASES;
   //  printf("i = %d j = %d angle = %f\n", i, j, cub->player.angle);
        if (cub->params.map[j][i] != '0' && cub->params.map[j][i] != 'W' && cub->params.map[j][i] != 'S' && cub->params.map[j][i] != 'N' && cub->params.map[j][i] != 'O')
                return (true);
        else
                return (false);
        
}

void	my_mlx_pixel_put(t_cub *cub, int x, int y, int color)
{
	char	*dst;

	dst = cub->mlx.addr + (y * cub->mlx.line_length + x * (cub->mlx.bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void draw_wall(int print_x, double ray_dist, t_cub *cub)
{
    
    double wall_height = ((double)64 / ray_dist) * (double)100;
    double wall_top = ((double)WIN_Y - wall_height) / (double)2;
    double wall_bottom = wall_top + wall_height;

    for (int y = (int)wall_top; y < (int)wall_bottom; y++)
    {
       if (cub->wall_data.side_color == 0)
                my_mlx_pixel_put(cub, print_x, y, 0xFF0000);
               //mlx_pixel_put(cub->mlx.mlx, cub->mlx.mlx_win, print_x, y, 0xFF0000); // Red color (0xFF0000)
        else if (cub->wall_data.side_color == 1)
               my_mlx_pixel_put(cub, print_x, y, 0xCC0000);
                //mlx_pixel_put(cub->mlx.mlx, cub->mlx.mlx_win, print_x, y, 0xCC0000);
                
    }
    mlx_put_image_to_window(cub->mlx.mlx, cub->mlx.mlx_win, cub->mlx.img, 0, 0);
}


void render(t_cub *cub) 
{
        t_raycast_data ray;
        cub->mlx.img = mlx_new_image(cub->mlx.mlx, WIN_X, WIN_Y);
        cub->mlx.addr = mlx_get_data_addr(cub->mlx.img, &cub->mlx.bits_per_pixel, &cub->mlx.line_length,
                                                                &cub->mlx.endian);      
        int counter = 0;
        int counter2 = 0;       
        double first_horizontal_intersection_x;
        double first_horizontal_intersection_y; 
        double first_vertical_intersection_x;
        double first_vertical_intersection_y;   
        int print_x = 0;        
        ray.angle_raycast_start = cub->player.angle + FOV / 2;
        if (ray.angle_raycast_start >= 360)
                ray.angle_raycast_start = fmod(ray.angle_raycast_start, 360);
        ray.angle_raycast_end = ray.angle_raycast_start - FOV;
        ray.angle_ray = (double)FOV / (double)WIN_X;

      // printf("pos x = %f pos y = %f\n", cub->player.pos.x, cub->player.pos.y);
//         int i = 0;
//        ray.angle_raycast_start = cub->player.angle;
//     while (i++ < 1)
    while (ray.angle_raycast_start > ray.angle_raycast_end)
    {
        cub->ray_dir_x = cos(ray.angle_raycast_start * (PI / 180));
        cub->ray_dir_y = -sin(ray.angle_raycast_start * (PI / 180));
        ray.x = cub->player.pos.x;
        ray.y = cub->player.pos.y;

        counter = 0;
        counter2 = 0;
        ray.horizontal_wall_dist = -1;
        while (ray.x >= 0 && ray.y >= 0 && ray.x && ray.y) 
        {
                //printf("ray x = %f ray y = %f\n", ray.x, ray.y);
                if (find_wall(cub, ray.x, ray.y))
                {
                        //printf("find wall\n");
                        ray.horizontal_wall_dist = sqrt(pow(ray.x - cub->player.pos.x, (double)2) + pow(ray.y - cub->player.pos.y, (double)2));
                        break;
                }
            if (fmod((int)ray.y, SIZE_OF_CASES) == 0)
            {
               // printf("counter = %d\n", counter);
                //printf("horizontal ray x = %f ray y = %f posx = %f pos y = %f\n", ray.x, ray.y, cub->player.pos.x, cub->player.pos.y);
                if (counter == 0)
                {
                        first_horizontal_intersection_x = ray.x;
                        first_horizontal_intersection_y = ray.y;
                }
                if (counter == 1)
                        ray.horizontal_step_x = sqrt(pow(ray.x - first_horizontal_intersection_x, (double)2) + pow(ray.y - first_horizontal_intersection_y, (double)2));
                counter++;
                if (ray.angle_raycast_start < (double)180)
                {
                        
                        if (find_wall(cub, ray.x, ray.y - (double)1))
                        {
                                ray.horizontal_wall_point_x = ray.x;
                                ray.horizontal_wall_point_y = ray.y;
                                ray.horizontal_wall_dist = sqrt(pow(ray.x - cub->player.pos.x, (double)2) + pow(ray.y - cub->player.pos.y, (double)2));
                                break;
                        }
                        
                }
                if (ray.angle_raycast_start >= (double)180)
                {
                        if (find_wall(cub, ray.x, ray.y + (double)1))
                        {
                                ray.horizontal_wall_point_x = ray.x;
                                ray.horizontal_wall_point_y = ray.y;
                                ray.horizontal_wall_dist = sqrt(pow(ray.x - cub->player.pos.x, (double)2) + pow(ray.y - cub->player.pos.y, (double)2));
                                
                                break;
                        }
                }
            }
            if (counter < 2)
            {
                ray.x += cub->ray_dir_x;
                ray.y += cub->ray_dir_y;
            }
            if (counter >= 2)
            {
                ray.x += ray.horizontal_step_x;
                ray.y += (double)SIZE_OF_CASES;
            }
        }

        ray.x = cub->player.pos.x;
        ray.y = cub->player.pos.y;
       ray.vertical_wall_dist = -1;
        while (ray.x >= 0 && ray.y >= 0 && ray.x && ray.y)
        {
                if (find_wall(cub, ray.x, ray.y))
                {

                        ray.vertical_wall_dist = sqrt(pow(ray.x - cub->player.pos.x, (double)2) + pow(ray.y - cub->player.pos.y, (double)2));
                        break;
                }

            if (fmod((int)ray.x, SIZE_OF_CASES) == 0)
            {
                //printf("counter2 = %d\n", counter2);
                if (counter2 == 0)
                {
                        first_vertical_intersection_x = ray.x;
                        first_vertical_intersection_y = ray.y;
                }
                if (counter2 == 1)
                        ray.vertical_step_y = sqrt(pow(ray.x - first_vertical_intersection_x, (double)2) + pow(ray.y - first_vertical_intersection_y, (double)2));
                counter2++;
                if (ray.angle_raycast_start <+ (double)270 && ray.angle_raycast_start > (double)90)
                {
                        if (find_wall(cub, ray.x - (double)1, ray.y))
                        {
                                ray.vertical_wall_point_x = ray.x;
                                ray.vertical_wall_point_y = ray.y;
                                ray.vertical_wall_dist = sqrt(pow(ray.x - cub->player.pos.x, (double)2) + pow(ray.y - cub->player.pos.y, (double)2));
                                break;
                        }
                }
                if (ray.angle_raycast_start <= (double)90 && ray.angle_raycast_start >= (double)270)
                {
                        if (find_wall(cub, ray.x + (double)1, ray.y))
                        {
                                ray.vertical_wall_point_x = ray.x;
                                ray.vertical_wall_point_y = ray.y;
                                ray.vertical_wall_dist = sqrt(pow(ray.x - cub->player.pos.x, (double)2) + pow(ray.y - cub->player.pos.y, (double)2));
                                break;
                        }
                }
            }
            if (counter2 < 2)
            {
                ray.x += cub->ray_dir_x;
                ray.y += cub->ray_dir_y;
            }
            if (counter2 >= 2)
            {
                ray.x += (double)SIZE_OF_CASES;
                ray.y += ray.vertical_step_y;
            }
        }

       
        if ((int)ray.horizontal_wall_dist > 0 && (int)ray.vertical_wall_dist > 0 && (int)ray.horizontal_wall_dist < (int)ray.vertical_wall_dist)
        {
                ray.dist = ray.horizontal_wall_dist;
                cub->wall_data.side_color = 0;
        }
        else if ((int)ray.horizontal_wall_dist < 0)
        {
                ray.dist = ray.vertical_wall_dist;
                cub->wall_data.side_color = 1;
        }
        else if ((int)ray.vertical_wall_dist < 0)
        {
                ray.dist = ray.horizontal_wall_dist;
                 cub->wall_data.side_color = 0;
        }
        else if ((int)ray.vertical_wall_dist > 0 && (int)ray.horizontal_wall_dist >= (int)ray.vertical_wall_dist)
        {
                ray.dist = ray.vertical_wall_dist;
                 cub->wall_data.side_color = 1;
        }

        //  printf("horizontal_wall_dist = %f\n", ray.horizontal_wall_dist);
        //  printf("vertical_wall_dist = %f\n", ray.vertical_wall_dist);
        //  printf("dist = %f\n", ray.dist);

        draw_wall(print_x, ray.dist, cub);
        ray.angle_raycast_start -= ray.angle_ray;
        print_x++;
    }
}
