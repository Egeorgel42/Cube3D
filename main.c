/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 11:43:57 by egeorgel          #+#    #+#             */
/*   Updated: 2023/09/20 16:53:51 by egeorgel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	initialize(t_cub *cub)
{
	cub->mlx.mlx = mlx_init();
	if (!cub->mlx.mlx)
		error(cub, ERRMLX, NULL);
	cub->mlx.mlx_win = mlx_new_window(cub->mlx.mlx, WIN_X, WIN_Y, "cub3D");
	if (SIZE_OF_CASES % 24 != 0)
		error(cub, INVALID_PARAM,
			" SIZE_OF_CASES must be multiple of 24 in cub3d.h");
	cub->player.pos.x = 0;
	cub->player.pos.y = 0;
	cub->keys.w = false;
	cub->keys.a = false;
	cub->keys.s = false;
	cub->keys.d = false;
	cub->keys.r_left = false;
	cub->keys.r_right = false;
	cub->win_x = WIN_X;
	cub->win_y = WIN_Y;
	cub->mv_scaling = SIZE_OF_CASES / 24;
	cub->degre_to_rad = PI / 180;
	cub->decrease_angle = (FOV * (PI / 180)) / WIN_X;
	cub->dist_to_projection_plane = (WIN_X / 2)
		/ (tan(FOV * cub->degre_to_rad / 2));
}

static int	run_game(t_cub *cub)
{
	movement(cub);
	render(cub);
	mlx_put_image_to_window(cub->mlx.mlx,
		cub->mlx.mlx_win, cub->view.img, 0, 0);
	return (0);
}

static int	end(void)
{
	exit(0);
}

int	main(int argc, char **argv)
{
	t_cub	cub;

	error_init(&cub);
	if (argc != 2)
		error(&cub, NB_ARG, NULL);
	initialize(&cub);
	get_params(&cub, argv[1]);
	create_image(&cub.mlx, &cub.view, WIN_X, WIN_Y);
	render(&cub);
	mlx_put_image_to_window(cub.mlx.mlx, cub.mlx.mlx_win, cub.view.img, 0, 0);
	mlx_hook(cub.mlx.mlx_win, 17, 0L, end, &cub);
	mlx_hook(cub.mlx.mlx_win, 02, 1L << 0, key_press, &cub);
	mlx_key_hook(cub.mlx.mlx_win, key_release, &cub);
	mlx_loop_hook(cub.mlx.mlx, run_game, &cub);
	mlx_loop(cub.mlx.mlx);
}
