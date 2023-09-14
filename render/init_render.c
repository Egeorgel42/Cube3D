#include "cub3d.h"

void    init_wall(t_cub *cub, double ray_dist)
{
        ray_dist = ray_dist * cos(cub->ray.new_ray_angle_rad);
        cub->wall_data.wall_height = (double)SIZE_OF_CASES / ray_dist * (double)DIST_TO_PROJECTION_PLANE;
        cub->wall_data.wall_top = ((double)WIN_Y - cub->wall_data.wall_height) / (double)2;
        cub->wall_data.wall_bottom = cub->wall_data.wall_top + cub->wall_data.wall_height;
        cub->ray.draw_y = (int)cub->wall_data.wall_top;
        if (cub->wall_data.wall_height >= WIN_Y)
        {
                cub->ray.draw_y = 0;
                cub->wall_data.wall_bottom = WIN_Y;
        }
}

void    init_horizontal_step_distance(t_cub *cub)
{
        if (cub->ray.ray_dir_y < 0)
        {
                cub->ray.dist_to_horizontal = cub->player.pos.y - ((int)(cub->player.pos.y/SIZE_OF_CASES) * (SIZE_OF_CASES));
                cub->ray.stepy = -1;
        }
        if (cub->ray.ray_dir_y > 0)
        {
                cub->ray.dist_to_horizontal = ((int)(cub->player.pos.y/SIZE_OF_CASES) * (SIZE_OF_CASES) + SIZE_OF_CASES) - cub->player.pos.y;
                cub->ray.stepy = 1;
        }
}

void    init_vertical_step_distance(t_cub *cub)
{
        if (cub->ray.ray_dir_x < 0)
        {
                cub->ray.dist_to_vertical = cub->player.pos.x - ((int)(cub->player.pos.x/SIZE_OF_CASES) * (SIZE_OF_CASES));
                cub->ray.stepx = -1;
        }
        if (cub->ray.ray_dir_x > 0)
        {
                cub->ray.dist_to_vertical = ((int)(cub->player.pos.x/SIZE_OF_CASES) * (SIZE_OF_CASES) + SIZE_OF_CASES) - cub->player.pos.x;
                cub->ray.stepx = 1;
        }
}

void    ray_init_step_distance(t_cub *cub)
{
        init_horizontal_step_distance(cub);
        init_vertical_step_distance(cub);
        cub->ray.dist_x = fabs(cub->ray.dist_to_vertical / cub->ray.ray_dir_x) ;
        if (fabs(cub->ray.ray_dir_y) == 0)
        {
                cub->ray.dist_y = 0.000;
                cub->ray.ray_dir_y = 0;
        }
        else
                cub->ray.dist_y = fabs(cub->ray.dist_to_horizontal / cub->ray.ray_dir_y);
}

void    ray_var_init(t_cub * cub)
{
        cub->ray.mapx = (int)(cub->player.pos.x / SIZE_OF_CASES);
        cub->ray.mapy = (int)(cub->player.pos.y / SIZE_OF_CASES);
         if (cub->ray.angle_raycast_rad < 0)
                cub->ray.angle_raycast_rad += 2*PI;
        if (cub->ray.angle_raycast_rad > 2*PI)
                cub->ray.angle_raycast_rad -= 2*PI;
        cub->ray.new_ray_angle_rad = -(cub->player.rad_angle - cub->ray.angle_raycast_rad);
        cub->ray.ray_dir_x = cos(cub->ray.angle_raycast_rad);
        cub->ray.ray_dir_y = -sin(cub->ray.angle_raycast_rad);
        cub->ray.x = cub->player.pos.x;
        cub->ray.y = cub->player.pos.y;
        ray_init_step_distance(cub);
}