/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 11:43:57 by egeorgel          #+#    #+#             */
/*   Updated: 2023/07/22 00:30:34 by egeorgel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_cub	cub;

	if (argc < 2)
		return (0);
	error_init(&cub);
	get_params(&cub, argv[1]);
	ft_printf("%d\n", *cub.params.res_x);
	ft_printf("%d\n", *cub.params.res_y);
	ft_printf("%s\n", cub.params.no);
}
