/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 11:43:57 by egeorgel          #+#    #+#             */
/*   Updated: 2023/08/03 16:58:49 by egeorgel         ###   ########.fr       */
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
	mlx_destroy_window(cub->mlx.mlx, cub->mlx.mlx_win);
}
//for unkown reasons if cub is not freed, leaks are present.

static int	run_game(t_cub *cub)
{
	minimap_update(cub);
	return (0);
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
	mlx_loop_hook(cub.mlx.mlx, run_game, &cub);
	mlx_loop(cub.mlx.mlx);
	free_cub(&cub);
}
