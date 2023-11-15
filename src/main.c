/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 12:08:03 by pehenri2          #+#    #+#             */
/*   Updated: 2023/11/15 16:35:23 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int argc, char **argv)
{
	t_fdf	fdf;

	if (parse_args_and_map(argc, argv, &fdf))
		return (EXIT_FAILURE);
	fdf.parallel.pixels = read_map(argv[1], &fdf.map_info);
	if (!fdf.parallel.pixels)
		return (EXIT_FAILURE);
	fdf.window = mlx_init(WIDTH, HEIGHT, "pehenri2 - fdf", true);
	if (!fdf.window)
		return (EXIT_FAILURE);
	fdf.image = mlx_new_image(fdf.window, WIDTH, HEIGHT);
	if (!fdf.image || (mlx_image_to_window(fdf.window, fdf.image, 0,
				0) < 0))
		return (EXIT_FAILURE);
	init_projections(&fdf);
	draw_map(fdf.current_map, fdf.map_info, &fdf);
	mlx_loop_hook(fdf.window, generic_key_hook, &fdf);
	mlx_loop(fdf.window);
	mlx_terminate(fdf.window);
	ft_free_ptr_array((void **)fdf.parallel.pixels, fdf.map_info.height);
	ft_free_ptr_array((void **)fdf.isometric.pixels, fdf.map_info.height);
	return (EXIT_SUCCESS);
}
