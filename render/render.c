#include "cub3d.h"

bool    find_wall(t_cub *cub, double x, double y)
{
        // double x1;
        // double y1;
        // x1 = x + cub->ray_dir_x;
        // y1 = y + cub->ray_dir_y;

        int i = (int)(x / SIZE_OF_CASES);
        int j = (int)(y / SIZE_OF_CASES);

        // int i = (int)(x1 / (double)SIZE_OF_CASES);
        // int j = (int)(y1 / (double)SIZE_OF_CASES);

       // printf("in wall x %f y = %f\n", x, y);

        printf("map[%d][%d] = %c\n", j, i, cub->params.map[j][i]);
   printf("i = %d j = %d angle = %f\n", i, j, cub->player.angle);
   printf("in wall ray x = %d ray y = %d\n", (int)x, (int)y);

        // if (cub->params.map[j][i] != '0' && cub->params.map[j][i] != 'W' && cub->params.map[j][i] != 'S' && cub->params.map[j][i] != 'N' && cub->params.map[j][i] != 'E')
        //         return (true);
        // else
        //         return (false);

        // if (cub->params.map[j][i] == '1' || cub->params.map[(int)((y - cub->ray_dir_y) / SIZE_OF_CASES)][i] == '1' || cub->params.map[j][(int)(((x - cub->ray_dir_x) / SIZE_OF_CASES))])
        //         return true;
        // else
        //         return false;

        // printf("test = %d\n", (int)(x + 1 / SIZE_OF_CASES));
        // printf("map[j][x + 1] = %c\n", cub->params.map[j][(int)((x + 1) / SIZE_OF_CASES)]);
        // printf("map[j][x - 1] = %c\n", cub->params.map[j][(int)((x - 1) / SIZE_OF_CASES)]);
        // printf("map[y + 1][i] = %c\n", cub->params.map[(int)((y + 1) / SIZE_OF_CASES)][i]);
        // printf("map[y + 1][i] = %c\n", cub->params.map[(int)((y - 1) / SIZE_OF_CASES)][i]);


        if (cub->params.map[j][(int)((x + 1.0) / SIZE_OF_CASES)] == '1' || cub->params.map[j][(int)((x - 1.0)/ SIZE_OF_CASES)] == '1' || cub->params.map[(int)((y + 1.0) / SIZE_OF_CASES)][i] == '1' || cub->params.map[(int)((y - 1.0) / SIZE_OF_CASES)][i] == '1')
                return true;
        else
                return false;
        
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
               mlx_pixel_put(cub->mlx.mlx, cub->mlx.mlx_win, print_x, y, 0xFF0000); // Red color (0xFF0000)
                //my_mlx_pixel_put(cub, print_x, y, 0xFF0000);
        else if (cub->wall_data.side_color == 1)
                mlx_pixel_put(cub->mlx.mlx, cub->mlx.mlx_win, print_x, y, 0x00FF00); // green
               //my_mlx_pixel_put(cub, print_x, y, 0xCC0000);
                
    }
    //mlx_put_image_to_window(cub->mlx.mlx, cub->mlx.mlx_win, cub->mlx.img, 0, 0);
}


void render(t_cub *cub) 
{
        t_raycast_data ray;
        // cub->mlx.img = mlx_new_image(cub->mlx.mlx, WIN_X, WIN_Y);
        // cub->mlx.addr = mlx_get_data_addr(cub->mlx.img, &cub->mlx.bits_per_pixel, &cub->mlx.line_length,
        //                                                         &cub->mlx.endian);      
                                                                
          
        int print_x = 0;        
        ray.angle_raycast_start = cub->player.angle + FOV / 2;
        if (ray.angle_raycast_start >= 360)
                ray.angle_raycast_start = fmod(ray.angle_raycast_start, 360);
        ray.angle_raycast_end = ray.angle_raycast_start - FOV;
        ray.angle_ray = (double)FOV / (double)WIN_X;

        double  angle_raycast_rad;
        double dist_to_vertical = 0;
        double dist_x;
        double dist_y;
        double wall_dist;
        double dist_to_horizontal = 0;
        int count;
        double relative_pos_x = cub->player.pos.x / (double)SIZE_OF_CASES - (int)cub->player.pos.x / SIZE_OF_CASES;
        double relative_pos_y = cub->player.pos.y / (double)SIZE_OF_CASES - (int)cub->player.pos.y / SIZE_OF_CASES;
        //double i;

        if (ray.angle_raycast_start < 270 && ray.angle_raycast_start >= 90)
                dist_to_vertical = fabs(relative_pos_x * (double)SIZE_OF_CASES);
        if (ray.angle_raycast_start < 90 || ray.angle_raycast_start >= 270)
                dist_to_vertical = fabs(relative_pos_x * (double)SIZE_OF_CASES - (double)SIZE_OF_CASES);
        if (ray.angle_raycast_start <= 180)
                dist_to_horizontal = fabs(relative_pos_y * (double)SIZE_OF_CASES);
        if (ray.angle_raycast_start > 180)
                dist_to_horizontal = fabs(relative_pos_y * (double)SIZE_OF_CASES - (double)SIZE_OF_CASES);
        printf("dist vertical = %f angle = %f\n", dist_to_vertical, ray.angle_raycast_start);
        printf("dist dist_to_horizontal = %f\n", dist_to_horizontal);

        printf("pos x = %f pos y = %f angle start = %f\n", cub->player.pos.x, cub->player.pos.y, ray.angle_raycast_start);

        // int j = 0;
        // ray.angle_raycast_start = cub->player.angle;
        // while (j++ < 1)
        while (ray.angle_raycast_start > ray.angle_raycast_end)
        {
                angle_raycast_rad = ray.angle_raycast_start * (PI / 180);
                cub->ray_dir_x = cos(angle_raycast_rad);
                cub->ray_dir_y = -sin(angle_raycast_rad);
                ray.x = cub->player.pos.x;
                ray.y = cub->player.pos.y;

                count = 0;
                //   i = 0;
                if (count == 0)
                {
                if (cub->ray_dir_x == 0.000)
                {
                        printf("icicicicic\n");
                        dist_x = 0.000;
                }
                else
                        dist_x = fabs(dist_to_vertical / cub->ray_dir_x);
                if (cub->ray_dir_y == 0.000)
                        dist_y = 0.000;
                else
                        dist_y = fabs(dist_to_horizontal / cub->ray_dir_y);
                }    
                printf("1 distx = %f  disty = %f\n", dist_x, dist_y);
                printf("ray x = %f  ray y = %f at start\n", ray.x, ray.y);

                while (1) 
                {

                        if (dist_x <= dist_y)
                        {
                                ray.x += cub->ray_dir_x * dist_x;
                                ray.y += cub->ray_dir_y * dist_x;
                                if (find_wall(cub, ray.x, ray.y))
                                {
                                        wall_dist = (int)dist_x;
                                        cub->wall_data.side_color = 0;
                                        ray.previous_ray_type = 0;
                                        printf("wall distx = %f angle = %f ray x = %f ray y %f\n", wall_dist, ray.angle_raycast_start, ray.x, ray.y);
                                        break;
                                }
                                printf("dist verticale = %f\n", dist_to_vertical);
                                dist_to_vertical = dist_to_vertical + (double)SIZE_OF_CASES;
                                dist_x = fabs(dist_to_vertical / cub->ray_dir_x);
                        }
                        else if (dist_y < dist_x)
                        {
                                ray.x += cub->ray_dir_x * dist_y;
                                ray.y += cub->ray_dir_y * dist_y;
                                if (find_wall(cub, ray.x, ray.y))
                                {
                                        wall_dist = (int)dist_y;
                                        ray.previous_ray_type = 1;
                                        cub->wall_data.side_color = 1;
                                        printf("wall distyy = %f angle = %f ray x = %f ray y %f\n", wall_dist, ray.angle_raycast_start, ray.x, ray.y);
                                        break;
                                }
                                dist_to_horizontal = dist_to_horizontal + (double)SIZE_OF_CASES;
                                dist_y = fabs(dist_to_horizontal / (cub->ray_dir_y));
                        }

                }       
                printf("distx = %f  disty = %f at end \n", dist_x, dist_y);
                printf("wall dist = %f\n", wall_dist);
                //draw_wall(print_x, wall_dist, cub);


                //to draw only the rays

                // Calcul des coordonnées de départ du trait
                double start_x = cub->player.pos.x;
                double start_y = cub->player.pos.y;

                // Calcul des coordonnées de fin du trait en fonction de la longueur wall_dist
                double end_x = start_x + cos(angle_raycast_rad) * wall_dist;
                double end_y = start_y - sin(angle_raycast_rad) * wall_dist;

                // Dessin du trait en utilisant une boucle
                int steps = (int)wall_dist;  // Nombre d'étapes à dessiner
                double step_x = (end_x - start_x) / steps;  // Pas horizontal
                double step_y = (end_y - start_y) / steps;  // Pas vertical

                // Parcours des étapes pour dessiner le trait
                for (int step = 0; step <= steps; step++)
                {
                    int x = (int)(start_x + step_x * step);
                    int y = (int)(start_y + step_y * step);

                    mlx_pixel_put(cub->mlx.mlx, cub->mlx.mlx_win, x, y, 0xFFFFFF);  // Dessiner un pixel
                }

                ray.angle_raycast_start -= ray.angle_ray;
                print_x++;
        }
}