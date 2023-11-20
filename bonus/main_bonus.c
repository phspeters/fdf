/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 12:08:03 by pehenri2          #+#    #+#             */
/*   Updated: 2023/11/19 21:41:09 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	free_maps(t_fdf *fdf)
{
	ft_free_ptr_array((void **)fdf->parallel.pixels, fdf->map_info.height);
	ft_free_ptr_array((void **)fdf->isometric.pixels, fdf->map_info.height);
}

void	handle_mlx_error(t_fdf *fdf)
{
	int	exit_code;

	free_maps(fdf);
	exit_code = ft_fprintf(STDERR_FILENO, "%s", mlx_strerror(mlx_errno));
	exit(exit_code);
}

void	draw_loop(void *param)
{
	t_fdf	*fdf;

	fdf = param;
	mlx_delete_image(fdf->window, fdf->image);
	fdf->image = mlx_new_image(fdf->window, WIDTH, HEIGHT);
	mlx_image_to_window(fdf->window, fdf->image, 0, 0);
	draw_map(fdf->current_map, fdf->map_info, fdf);
}

void	action_hooks(t_fdf *fdf)
{
	mlx_key_hook(fdf->window, close_key_hook, fdf);
	mlx_key_hook(fdf->window, translate_key_hook, fdf);
	mlx_key_hook(fdf->window, rotate_key_hook, fdf);
	mlx_key_hook(fdf->window, zoom_key_hook, fdf);
	mlx_key_hook(fdf->window, select_projection_key_hook, fdf);
	mlx_key_hook(fdf->window, zoom_scroll_hook, fdf);
}

int	main(int argc, char **argv)
{
	t_fdf	fdf;

	if (parse_args_and_map(argc, argv, &fdf))
		return (EXIT_FAILURE);
	fdf.parallel.pixels = read_map(argv[1], &fdf.map_info);
	if (!fdf.parallel.pixels)
		return (EXIT_FAILURE);
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	fdf.window = mlx_init(WIDTH, HEIGHT, "pehenri2 - fdf", true);
	if (!fdf.window)
		handle_mlx_error(&fdf);
	fdf.image = mlx_new_image(fdf.window, WIDTH, HEIGHT);
	if (!fdf.image || (mlx_image_to_window(fdf.window, fdf.image, 0,
				0) < 0))
		handle_mlx_error(&fdf);
	init_projections(&fdf);
	action_hooks(&fdf);
	mlx_loop_hook(fdf.window, draw_loop, &fdf);
	mlx_loop(fdf.window);
	mlx_terminate(fdf.window);
	free_maps(&fdf);
	return (EXIT_SUCCESS);
}
