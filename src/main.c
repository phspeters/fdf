/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 12:08:03 by pehenri2          #+#    #+#             */
/*   Updated: 2023/11/02 15:18:29 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

//***** Remember to initiate structs
#include <stdio.h>

int	main(int argc, char **argv)
{
	t_master	master;

	if (parse_args_and_map(argc, argv, &master))
		return (EXIT_FAILURE);
	master.pixels = read_map(argv[1], master.map_width, master.map_height);
	if (!master.pixels)
		return (EXIT_FAILURE);
	master.window = mlx_init(WIDTH, HEIGHT, "pehenri2 - fdf", true);
	if (!master.window)
		return (EXIT_FAILURE);
	master.image = mlx_new_image(master.window, WIDTH, HEIGHT);
	if (!master.image || (mlx_image_to_window(master.window, master.image, 0,
				0) < 0))
		return (EXIT_FAILURE);
	master.zoom = 5;
	master.x_offset = (WIDTH / 2) - (master.map_width / 2);
	master.y_offset = (HEIGHT / 4) - (master.map_height / 2);
	mlx_loop_hook(master.window, generic_key_hook, &master);
	draw_map(&master, master.map_height, master.map_width);
	mlx_loop(master.window);
	mlx_terminate(master.window);
	ft_free_ptr_array((void **)master.pixels, master.map_height);
	return (EXIT_SUCCESS);
}
