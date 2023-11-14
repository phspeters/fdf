/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 12:08:03 by pehenri2          #+#    #+#             */
/*   Updated: 2023/11/08 12:20:30 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
	init_camera(&master);
	draw_map(&master, master.map_height, master.map_width);
	mlx_loop_hook(master.window, generic_key_hook, &master);
	mlx_loop(master.window);
	mlx_terminate(master.window);
	ft_free_ptr_array((void **)master.pixels, master.map_height);
	return (EXIT_SUCCESS);
}
