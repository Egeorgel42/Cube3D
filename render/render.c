#include "cub3d.h"

// void	my_mlx_pixel_put(t_cub *cub, int x, int y, int color)
// {
// 	char	*dst;

// 	dst = cub->mlx.addr + (y * cub->mlx.line_length + x * (cub->mlx.bits_per_pixel / 8));
// 	*(unsigned int*)dst = color;
// }

// void    pixel_to_image(t_cub *cub)
// {
//         char    *pixel;
//         int     color;

//         pixel = cub->params.texture->img.addr + ((int)cub->params.texture->texy * cub->params.texture->img.line_length + (int)cub->params.texture->texx * (cub->params.texture->img.bits_per_pixel / 8));
//         color = *(int *)pixel;
//         my_mlx_pixel_put(cub, cub->ray.print_x, cub->ray.draw_y, color);
// }

// void    draw_floor(t_cub *cub)
// {
//         int y = cub->ray.draw_y;
//         while (y < WIN_Y)
//         {
//                 my_mlx_pixel_put(cub, cub->ray.print_x, y, *cub->params.floor_color);
//                 y++;
//         }
// }

// void draw_sky(t_cub *cub)
// {
//         int y = cub->wall_data.wall_top - 1;
//         while (y > -1 )
//         {
//                 my_mlx_pixel_put(cub, cub->ray.print_x, y, *cub->params.ceiling_color);
//                 y--;
//         }
// }

void    set_texture(t_cub *cub)
{
        if (cub->wall_data.side_color == 1 && cub->ray.ray_dir_y < 0) //horizontal
        {
                cub->params.texture = &cub->params.texture_north;
                cub->params.texture->wallx = (int)cub->ray.x % SIZE_OF_CASES;
        }
        else if (cub->wall_data.side_color == 1 && cub->ray.ray_dir_y > 0)
        {
                cub->params.texture = &cub->params.texture_south;
                cub->params.texture->wallx = SIZE_OF_CASES - (int)cub->ray.x % SIZE_OF_CASES;
        }
        if (cub->wall_data.side_color == 0 && cub->ray.ray_dir_x < 0)//vertical
        {
                cub->params.texture = &cub->params.texture_east;
                cub->params.texture->wallx = SIZE_OF_CASES - (int)cub->ray.y % SIZE_OF_CASES;
        }
        else if (cub->wall_data.side_color == 0 && cub->ray.ray_dir_x > 0)
        {
                cub->params.texture = &cub->params.texture_west;
                cub->params.texture->wallx = (int)cub->ray.y % SIZE_OF_CASES;
        }
}

// void    init_wall(t_cub *cub, double ray_dist)
// {
//         ray_dist = ray_dist * cos(cub->ray.new_ray_angle_rad);
//         cub->wall_data.wall_height = (double)SIZE_OF_CASES / ray_dist * (double)DIST_TO_PROJECTION_PLANE;
//         cub->wall_data.wall_top = ((double)WIN_Y - cub->wall_data.wall_height) / (double)2;
//         cub->wall_data.wall_bottom = cub->wall_data.wall_top + cub->wall_data.wall_height;
//         cub->ray.draw_y = (int)cub->wall_data.wall_top;
//         if (cub->wall_data.wall_height >= WIN_Y)
//         {
//                 cub->ray.draw_y = 0;
//                 cub->wall_data.wall_bottom = WIN_Y;
//         }
// }

// void draw_wall(double ray_dist, t_cub *cub)
// {
//         init_wall(cub, ray_dist);
//         set_texture(cub);
//         cub->params.texture->texx = cub->params.texture->wallx;
//         cub->params.texture->texy = 0;
//         if (cub->wall_data.wall_height >= WIN_Y)
//                 cub->params.texture->texy = (((cub->wall_data.wall_height - WIN_Y) / 2) / cub->wall_data.wall_height) * SIZE_OF_CASES;
//         //texture->texy = (cub->ray.draw_y - WIN_Y / 2 + cub->wall_data.wall_height / 2) * (texture->img.height / (double)cub->wall_data.wall_height);
//         while ( cub->ray.draw_y < (int)cub->wall_data.wall_bottom && cub->ray.draw_y < WIN_Y && cub->params.texture->texy < cub->params.texture->img.height - 1)
//         {       
//                 pixel_to_image(cub);
//                 cub->ray.draw_y++;
//                 cub->params.texture->texy += cub->params.texture->img.height / (double)cub->wall_data.wall_height;
//         }
//         draw_floor(cub);
//         draw_sky(cub);
// }

// void    init_horizontal_step_distance(t_cub *cub)
// {
//         if (cub->ray.ray_dir_y < 0)
//         {
//                 cub->ray.dist_to_horizontal = cub->player.pos.y - ((int)(cub->player.pos.y/SIZE_OF_CASES) * (SIZE_OF_CASES));
//                 cub->ray.stepy = -1;
//         }
//         if (cub->ray.ray_dir_y > 0)
//         {
//                 cub->ray.dist_to_horizontal = ((int)(cub->player.pos.y/SIZE_OF_CASES) * (SIZE_OF_CASES) + SIZE_OF_CASES) - cub->player.pos.y;
//                 cub->ray.stepy = 1;
//         }
// }

// void    init_vertical_step_distance(t_cub *cub)
// {
//         if (cub->ray.ray_dir_x < 0)
//         {
//                 cub->ray.dist_to_vertical = cub->player.pos.x - ((int)(cub->player.pos.x/SIZE_OF_CASES) * (SIZE_OF_CASES));
//                 cub->ray.stepx = -1;
//         }
//         if (cub->ray.ray_dir_x > 0)
//         {
//                 cub->ray.dist_to_vertical = ((int)(cub->player.pos.x/SIZE_OF_CASES) * (SIZE_OF_CASES) + SIZE_OF_CASES) - cub->player.pos.x;
//                 cub->ray.stepx = 1;
//         }
// }

// void    ray_init_step_distance(t_cub *cub)
// {
//         init_horizontal_step_distance(cub);
//         init_vertical_step_distance(cub);
//         cub->ray.dist_x = fabs(cub->ray.dist_to_vertical / cub->ray.ray_dir_x) ;
//         if (fabs(cub->ray.ray_dir_y) == 0)
//         {
//                 cub->ray.dist_y = 0.000;
//                 cub->ray.ray_dir_y = 0;
//         }
//         else
//                 cub->ray.dist_y = fabs(cub->ray.dist_to_horizontal / cub->ray.ray_dir_y);
// }

// void    ray_var_init(t_cub * cub)
// {
//         cub->ray.mapx = (int)(cub->player.pos.x / SIZE_OF_CASES);
//         cub->ray.mapy = (int)(cub->player.pos.y / SIZE_OF_CASES);
//          if (cub->ray.angle_raycast_rad < 0)
//                 cub->ray.angle_raycast_rad += 2*PI;
//         if (cub->ray.angle_raycast_rad > 2*PI)
//                 cub->ray.angle_raycast_rad -= 2*PI;
//         cub->ray.new_ray_angle_rad = -(cub->player.rad_angle - cub->ray.angle_raycast_rad);
//         cub->ray.ray_dir_x = cos(cub->ray.angle_raycast_rad);
//         cub->ray.ray_dir_y = -sin(cub->ray.angle_raycast_rad);
//         cub->ray.x = cub->player.pos.x;
//         cub->ray.y = cub->player.pos.y;
//         ray_init_step_distance(cub);
// }

int cast_ray_horizontal(t_cub *cub)
{
        cub->ray.mapx += cub->ray.stepx;
        cub->ray.x += cub->ray.ray_dir_x * cub->ray.dist_x;
        cub->ray.y += cub->ray.ray_dir_y * cub->ray.dist_x;
        
        if (cub->params.map[cub->ray.mapy][cub->ray.mapx] == '1')
        {
            cub->ray.wall_dist = cub->ray.dist_x;
            cub->wall_data.side_color = 0;
            return true;
        }
        cub->ray.dist_to_vertical = cub->ray.dist_to_vertical + (double)SIZE_OF_CASES;
        cub->ray.dist_x = fabs(cub->ray.dist_to_vertical / cub->ray.ray_dir_x);
        return false;
}

int cast_ray_vertical(t_cub *cub)
{
        cub->ray.mapy += cub->ray.stepy;
        cub->ray.x += cub->ray.ray_dir_x * cub->ray.dist_y;
        cub->ray.y += cub->ray.ray_dir_y * cub->ray.dist_y;

        if (cub->params.map[cub->ray.mapy][cub->ray.mapx] == '1')
        {
            cub->ray.wall_dist = cub->ray.dist_y;
            cub->wall_data.side_color = 1;
            return true;
        }

        cub->ray.dist_to_horizontal = cub->ray.dist_to_horizontal + (double)SIZE_OF_CASES;
        cub->ray.dist_y = fabs(cub->ray.dist_to_horizontal / cub->ray.ray_dir_y);
        return false;
}

void find_dist(t_cub *cub)
{
        while (cub->ray.x >= 0 && cub->ray.y >= 0) 
        {
                cub->ray.x = cub->player.pos.x;
                cub->ray.y = cub->player.pos.y;
                cub->ray.wall_dist = 0;

                if ((cub->ray.dist_x < cub->ray.dist_y) || fabs(cub->ray.ray_dir_y) == 0)
                        if (cast_ray_horizontal(cub))
                                break;      
                cub->ray.x = cub->player.pos.x;
                cub->ray.y = cub->player.pos.y;
                cub->ray.wall_dist = 0;
                if (cub->ray.dist_y < cub->ray.dist_x)
                        if (cast_ray_vertical(cub))
                                break;
        }
}

void render(t_cub *cub) 
{
        cub->mlx.img = mlx_new_image(cub->mlx.mlx, WIN_X, WIN_Y);
        cub->mlx.addr = mlx_get_data_addr(cub->mlx.img, &cub->mlx.bits_per_pixel, &cub->mlx.line_length,
                                                                &cub->mlx.endian); 
        cub->ray.print_x = 0; 
        cub->player.rad_angle = cub->player.angle * DEGRE_TO_RAD;
        cub->ray.angle_raycast_rad = cub->player.rad_angle + (FOV * DEGRE_TO_RAD/ 2);
        while (cub->ray.print_x < WIN_X)
        {
                ray_var_init(cub);
                find_dist(cub);
                draw_wall(cub->ray.wall_dist, cub);
                cub->ray.angle_raycast_rad -= DECREASE_ANGLE;
                cub->ray.print_x++;
        }
        mlx_put_image_to_window(cub->mlx.mlx, cub->mlx.mlx_win, cub->mlx.img, 0, 0);
        mlx_destroy_image(cub->mlx.mlx, cub->mlx.img);
}