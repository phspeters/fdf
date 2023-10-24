/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 12:08:03 by pehenri2          #+#    #+#             */
/*   Updated: 2023/10/24 16:29:22 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// MLX allows you to define its core behaviour before startup.

/* Do stuff */

// Create and display the image.
// Even after the image is being displayed, we can still modify the buffer.
// Register a hook and pass mlx as an optional param.

// NOTE: Do this before calling mlx_loop!

//***** Remember to initiate structs
int	main(int argc, char **argv)
{
	t_master	master;

	if (parse_args_and_map(argc, argv, &master))
		return (EXIT_FAILURE);
	ft_printf("Height: %u\n", master.map_height);
	ft_printf("Width: %u\n", master.map_width);
	//master.pixels = read_map(argv[1], master.map_width, master.map_height);
	//ft_free_ptr_array(master.pixels);
	//mlx_set_setting(MLX_MAXIMIZED, true);
	//master.window = mlx_init(WIDTH, HEIGHT, "pehenri2 - fdf", true);
	//if (!master.window)
	//	return (EXIT_FAILURE);
	//master.image = mlx_new_image(master.window, 256, 256);
	//if (!master.image || (mlx_image_to_window(master.window, master.image, 0,
	//			0) < 0))
	//	return (EXIT_FAILURE);
	//mlx_put_pixel(master.image, 0, 0, 0xFF0000FF);
	//mlx_loop(master.window);
	//mlx_terminate(master.window);
	return (EXIT_SUCCESS);
}
