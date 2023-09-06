#include "cub3d.h"

bool    find_wall(t_cub *cub, double x, double y)
{
        // double x1;
        // double y1;
        // x1 = x + cub->ray_dir_x;
        // y1 = y + cub->ray_dir_y;

//// point on left
// double x2 = x - cub->ray_dir_y -1;
// double y2 = y + cub->ray_dir_x + 1;
// // point on right
// double x3 = x + cub->ray_dir_y + 1;
// double y3 = y - cub->ray_dir_x - 1;


        int i = (int)(x / SIZE_OF_CASES);
        int j = (int)(y / SIZE_OF_CASES);

        // int i1 = (int)(x1 / (double)SIZE_OF_CASES);
        // int j1 = (int)(y1 / (double)SIZE_OF_CASES);

        // int i2 = (int)(x2 / (double)SIZE_OF_CASES);
        // int j2 = (int)(y2 / (double)SIZE_OF_CASES); 

        // int i3 = (int)(x3 / (double)SIZE_OF_CASES);
        // int j3 = (int)(y3 / (double)SIZE_OF_CASES);



        if (cub->ray.dist_y < cub->ray.dist_x && cub->params.map[j][i] == '1' && cub->params.map[j - 1][i] == '1')
                return false;
        if (cub->ray.dist_x < cub->ray.dist_y && cub->params.map[j][i] == '1' && cub->params.map[j][i - 1] == '1')
                return false;
        // if (cub->params.map[j][i] == '0' && cub->params.map[j2][i2] == '1' && cub->params.map[j3][i3] == '1')
        //         return true;
        if (cub->params.map[j][i] == '1' )//|| cub->params.map[j1][i1] == '1')
                return true;
        else  
                return false;

        
        //// tester un a la fois des cas suivant :

        // if (cub->params.map[j][i] != '0' && cub->params.map[j][i] != 'W' && cub->params.map[j][i] != 'S' && cub->params.map[j][i] != 'N' && cub->params.map[j][i] != 'E')
        //         return (true);
        // else
        //         return (false);

        // if (cub->params.map[(int)(y / (double)SIZE_OF_CASES)][(int)(x / (double)SIZE_OF_CASES)] == '1' || cub->params.map[(int)((y + 1) / (double)SIZE_OF_CASES)][(int)((x + 1) / (double)SIZE_OF_CASES)] == '1' || cub->params.map[(int)((y - 1) / (double)SIZE_OF_CASES)][(int)((x - 1) / (double)SIZE_OF_CASES)] == '1')
        //         return true;
        // else
        //         return false;

        // if (cub->params.map[(int)((y + cub->ray_dir_y) / SIZE_OF_CASES)][i] == '1' || cub->params.map[j][i] == '1' || cub->params.map[j][(int)(((x + cub->ray_dir_x) / SIZE_OF_CASES))] == '1')
        //         return true;
        // else
        //         return false;


        // if (cub->params.map[j][(int)((x + 1.0) / SIZE_OF_CASES)] == '1' || cub->params.map[j][(int)((x - 1.0)/ SIZE_OF_CASES)] == '1' || cub->params.map[(int)((y + 1.0) / SIZE_OF_CASES)][i] == '1' || cub->params.map[(int)((y - 1.0) / SIZE_OF_CASES)][i] == '1')
        //         return true;
        // else
        //         return false;
        

        // if (cub->params.map[j][(int)((x + cub->ray_dir_x) / SIZE_OF_CASES)] == '1' || cub->params.map[j][(int)((x - cub->ray_dir_x)/ SIZE_OF_CASES)] == '1' || cub->params.map[(int)((y + cub->ray_dir_y) / SIZE_OF_CASES)][i] == '1' || cub->params.map[(int)((y - cub->ray_dir_y) / SIZE_OF_CASES)][i] == '1')
        //         return true;
        // else
        //         return false;
        
}

void	my_mlx_pixel_put(t_cub *cub, int x, int y, int color)
{
	char	*dst;

	dst = cub->mlx.addr + (y * cub->mlx.line_length + x * (cub->mlx.bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	my_mlx_pixel_put2(t_cub *cub, int x, int y, int color)
{
	char	*dst;

	dst = cub->mlx.addr2 + (y * cub->mlx.line_length + x * (cub->mlx.bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void draw_wall(int print_x, double ray_dist, t_cub *cub)
{
//     double anti_fisheye_angle;
//     anti_fisheye_angle = cub->ray.angle_raycast_rad - cub->player.angle * (PI / 180);

//     ray_dist = ray_dist * cos(anti_fisheye_angle);
        double wall_height = ((double)SIZE_OF_CASES / ray_dist) * (double)100;
        double wall_top = ((double)WIN_Y - wall_height) / (double)2;
        double wall_bottom = wall_top + wall_height;
        int y = (int)wall_top;
        if (wall_height >= WIN_Y)
        {
                y = 0;
                wall_bottom = WIN_Y;
        }
        while ( y < (int)wall_bottom && y < WIN_Y && print_x < WIN_X)
        {
                if (cub->wall_data.side_color == 0)
                         my_mlx_pixel_put(cub, print_x, y, 0xFF0000);//red
                else if (cub->wall_data.side_color == 1)
                        my_mlx_pixel_put(cub, print_x, y, 0x00FF00);//green
                y++;
        }
}

void render(t_cub *cub) 
{
        cub->mlx.img = mlx_new_image(cub->mlx.mlx, WIN_X, WIN_Y);
        cub->mlx.addr = mlx_get_data_addr(cub->mlx.img, &cub->mlx.bits_per_pixel, &cub->mlx.line_length,
                                                                &cub->mlx.endian);
                                                                
          
        int print_x = 0;        
        cub->ray.angle_raycast_start = cub->player.angle + FOV / 2;
        if (cub->ray.angle_raycast_start >= 360)
                cub->ray.angle_raycast_start = fmod(cub->ray.angle_raycast_start, 360);
        cub->ray.angle_raycast_end = cub->ray.angle_raycast_start - FOV;
        cub->ray.angle_ray = (double)FOV / (double)WIN_X;

        double dist_to_vertical = 0;
        double wall_dist;
        double dist_to_horizontal = 0;

        // int j = 0;
        // cub->ray.angle_raycast_start = cub->player.angle;
        // // //cub->ray.angle_raycast_start = 0.2;
        // while (j++ < 1)
       while (cub->ray.angle_raycast_start > cub->ray.angle_raycast_end)
        {
                cub->ray.angle_raycast_rad = cub->ray.angle_raycast_start * (PI / 180);
                cub->ray_dir_x = cos(cub->ray.angle_raycast_rad);
                cub->ray_dir_y = -sin(cub->ray.angle_raycast_rad);
                cub->ray.x = cub->player.pos.x;
                cub->ray.y = cub->player.pos.y;


                if (cub->ray_dir_y < 0)
                        dist_to_horizontal = (int)cub->player.pos.y - ((int)(cub->player.pos.y/SIZE_OF_CASES) * (SIZE_OF_CASES) - 1);
                if (cub->ray_dir_y >= 0)
                        dist_to_horizontal = ((int)(cub->player.pos.y/SIZE_OF_CASES) * (SIZE_OF_CASES) + SIZE_OF_CASES) - (int)cub->player.pos.y;
                if (cub->ray_dir_x < 0)
                        dist_to_vertical = (int)cub->player.pos.x - ((int)(cub->player.pos.x/SIZE_OF_CASES) * (SIZE_OF_CASES) - 1);
                if (cub->ray_dir_x >= 0)
                        dist_to_vertical = ((int)(cub->player.pos.x/SIZE_OF_CASES) * (SIZE_OF_CASES) + SIZE_OF_CASES) - (int)cub->player.pos.x;
                // printf("dist vertical = %f\n", dist_to_vertical);
                // printf("dist horizontal = %f\n", dist_to_horizontal);
                cub->ray.dist_x = fabs(dist_to_vertical / cub->ray_dir_x);
                if (fabs(cub->ray_dir_y) == 0)
                {
                        cub->ray.dist_y = 0.000;
                        cub->ray_dir_y = 0;
                }
                else
                        cub->ray.dist_y = fabs(dist_to_horizontal / cub->ray_dir_y);
                // printf("dist_x = %f  dist_y = %f\n", cub->ray.dist_x, cub->ray.dist_y);
                // printf("cub->ray_dir_y = %f cub->ray_dir_x = %f\n", cub->ray_dir_y, cub->ray_dir_x);

                while (cub->ray.x >= 0 && cub->ray.y >= 0) 
                {
                        cub->ray.x = cub->player.pos.x;
                        cub->ray.y = cub->player.pos.y;
                        wall_dist = 0;
                        if ((cub->ray.dist_x < cub->ray.dist_y) || fabs(cub->ray_dir_y) == 0)
                        {
                                cub->ray.x += cub->ray_dir_x * cub->ray.dist_x;
                                cub->ray.y += cub->ray_dir_y * cub->ray.dist_x;
                                if (find_wall(cub, cub->ray.x, cub->ray.y))
                                {
                                        wall_dist = cub->ray.dist_x;
                                        cub->wall_data.side_color = 0;
                                        cub->ray.previous_ray_type = 0;
                                        break;
                                }
                                dist_to_vertical = dist_to_vertical + (double)SIZE_OF_CASES;
                                cub->ray.dist_x = fabs(dist_to_vertical / cub->ray_dir_x);
                        }
                        cub->ray.x = cub->player.pos.x;
                        cub->ray.y = cub->player.pos.y;
                        wall_dist = 0;
                        if (cub->ray.dist_y < cub->ray.dist_x)
                        {
                                cub->ray.x += cub->ray_dir_x * cub->ray.dist_y;
                                cub->ray.y += cub->ray_dir_y * cub->ray.dist_y;
                                if (find_wall(cub, cub->ray.x, cub->ray.y))
                                {
                                        wall_dist = cub->ray.dist_y;
                                        cub->ray.previous_ray_type = 1;
                                        cub->wall_data.side_color = 1;
                                        break;
                                }
                                dist_to_horizontal = dist_to_horizontal + (double)SIZE_OF_CASES;
                                cub->ray.dist_y = fabs(dist_to_horizontal / (cub->ray_dir_y));
                        }

                }       
                // printf("distx = %f  disty = %f at end \n", cub->ray.dist_x, cub->ray.dist_y);
                // printf("wall dist = %f\n", wall_dist);

                draw_wall(print_x, wall_dist, cub);

                // //to draw only the rays

                // //Calcul des coordonnées de départ du trait
                // double start_x = cub->player.pos.x;
                // double start_y = cub->player.pos.y;

                // // Calcul des coordonnées de fin du trait en fonction de la longueur wall_dist
                // double end_x = start_x + cos(cub->ray.angle_raycast_rad) * wall_dist;
                // double end_y = start_y - sin(cub->ray.angle_raycast_rad) * wall_dist;

                // //  double end_x = start_x + cub->ray_dir_x * 20;
                // // double end_y = start_y - cub->ray_dir_y * 20;

                // // Dessin du trait en utilisant une boucle
                // int steps = (int)wall_dist;  // Nombre d'étapes à dessiner
                // double step_x = (end_x - start_x) / steps;  // Pas horizontal
                // double step_y = (end_y - start_y) / steps;  // Pas vertical

                // // Parcours des étapes pour dessiner le trait
                // for (int step = 0; step <= steps; step++)
                // {
                //     int x = (int)(start_x + step_x * step);
                //     int y = (int)(start_y + step_y * step);
                //     //if (cub->i % 2 == 0)
                //     if (cub->wall_data.side_color == 0)
                //         my_mlx_pixel_put(cub, x, y, 0xFF0000);  // Dessiner un pixel
                //     if (cub->wall_data.side_color == 1)
                //         my_mlx_pixel_put(cub, x, y, 0x00FF00);
                // //     if (cub->i % 2 != 0)
                // //         my_mlx_pixel_put2(cub, x, y, 0xFFFFFF);
                // }

                cub->ray.angle_raycast_start -= cub->ray.angle_ray;
                print_x++;
        }
        mlx_put_image_to_window(cub->mlx.mlx, cub->mlx.mlx_win, cub->mlx.img, 0, 0);
        mlx_destroy_image(cub->mlx.mlx, cub->mlx.img);
}