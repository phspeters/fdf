/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 12:08:03 by pehenri2          #+#    #+#             */
/*   Updated: 2023/11/14 19:08:33 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
// ler o mapa e guardar no parallel, iniciar
int	main(int argc, char **argv)
{
	t_fdf	fdf;

	if (parse_args_and_map(argc, argv, &fdf))
		return (EXIT_FAILURE);
	fdf.projections.parallel.pixels = read_map(argv[1], fdf);
	if (!fdf.projections.parallel.pixels)
		return (EXIT_FAILURE);
	fdf.window = mlx_init(WIDTH, HEIGHT, "pehenri2 - fdf", true);
	if (!fdf.window)
		return (EXIT_FAILURE);
	fdf.image = mlx_new_image(fdf.window, WIDTH, HEIGHT);
	if (!fdf.image || (mlx_image_to_window(fdf.window, fdf.image, 0,
				0) < 0))
		return (EXIT_FAILURE);
	init_projections(&fdf);
	init_camera(&fdf);
	draw_map(&fdf, fdf.projections.map_height, fdf.projections.map_width);
	mlx_loop_hook(fdf.window, generic_key_hook, &fdf);
	mlx_loop(fdf.window);
	mlx_terminate(fdf.window);
	ft_free_ptr_array((void **)fdf.projections.parallel.pixels, fdf.projections.map_height);
	//ft_free_ptr_array((void **)fdf.projections.isometric.pixels, fdf.projections.map_height);
	return (EXIT_SUCCESS);
}
