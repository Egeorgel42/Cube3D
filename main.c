/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 11:43:57 by egeorgel          #+#    #+#             */
/*   Updated: 2023/08/08 16:43:04 by egeorgel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	initialize(t_cub *cub)
{
	cub->mlx.mlx = mlx_init();
	if (!cub->mlx.mlx)
		error(cub, ERRMLX, NULL);
	cub->mlx.mlx_win = mlx_new_window(cub->mlx.mlx, WIN_X, WIN_Y, "cub3D");
	cub->player.pos.x = 0;
	cub->player.pos.y = 0;
	cub->keys.w = false;
	cub->keys.a = false;
	cub->keys.s = false;
	cub->keys.d = false;
	cub->keys.r_left = false;
	cub->keys.r_right = false;
}

static void	free_cub(t_cub *cub)
{
	freetab((void **)cub->errors);
	freetab((void **)cub->params.map);
	free(cub->params.n_text);
	free(cub->params.s_text);
	free(cub->params.e_text);
	free(cub->params.w_text);
	free(cub->params.ceiling_color);
	free(cub->params.floor_color);
	mlx_destroy_image(cub->mlx.mlx, cub->minimap.img.img);
	mlx_destroy_window(cub->mlx.mlx, cub->mlx.mlx_win);
}
//for unkown reasons if cub is not freed, leaks are present.

static int	run_game(t_cub *cub)
{
	if (movement(cub))
		minimap_update(cub);
	return (0);
}

static int	end(void)
{
	exit(0);
}

int	main(int argc, char **argv)
{
	t_cub	cub;

	if (argc < 2)
		return (0);
	error_init(&cub);
	initialize(&cub);
	get_params(&cub, argv[1]);
	minimap_initialize(&cub);
	minimap_update(&cub);
	ft_printf("%s\n", cub.params.n_text);
	ft_printf("%s\n", cub.params.s_text);
	ft_printf("%s\n", cub.params.w_text);
	ft_printf("%s\n", cub.params.e_text);
	ft_printf("%d\n", *cub.params.floor_color);
	ft_printf("%d\n", *cub.params.ceiling_color);

	int	i;
	i = -1;
	while (cub.params.map[++i])
		ft_printf("%s\n", cub.params.map[i]);
	mlx_hook(cub.mlx.mlx_win, 17, 0L, end, &cub);
	mlx_hook(cub.mlx.mlx_win, 02, 1L << 0, key_press, &cub);
	mlx_key_hook(cub.mlx.mlx_win, key_release, &cub);
	mlx_loop_hook(cub.mlx.mlx, run_game, &cub);
	mlx_loop(cub.mlx.mlx);
	free_cub(&cub);
}
