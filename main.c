/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 11:43:57 by egeorgel          #+#    #+#             */
/*   Updated: 2023/07/23 15:52:48 by egeorgel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	free_cub(t_cub *cub)
{
	freetab((void **)cub->errors);
	free(cub->params.res_x);
	free(cub->params.res_y);
	free(cub->params.n_text);
	free(cub->params.s_text);
	free(cub->params.e_text);
	free(cub->params.w_text);
	free(cub->params.ceiling_color);
	free(cub->params.floor_color);
	free(cub->params.sprite_text);
}
//for unkown reasons if cub is not freed, leaks are present.

int	main(int argc, char **argv)
{
	t_cub	cub;

	if (argc < 2)
		return (0);
	error_init(&cub);
	get_params(&cub, argv[1]);
	ft_printf("%d\n", *cub.params.res_x);
	ft_printf("%d\n", *cub.params.res_y);
	ft_printf("%s\n", cub.params.n_text);
	ft_printf("%s\n", cub.params.s_text);
	ft_printf("%s\n", cub.params.w_text);
	ft_printf("%s\n", cub.params.e_text);
	ft_printf("%s\n", cub.params.sprite_text);
	ft_printf("%d\n", *cub.params.floor_color);
	ft_printf("%d\n", *cub.params.ceiling_color);
	free_cub(&cub);
}
