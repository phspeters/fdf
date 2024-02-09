/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 12:08:03 by pehenri2          #+#    #+#             */
/*   Updated: 2024/02/07 18:50:59 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/**
 * @brief The main function of the program. It parses the arguments and checks
 * if the map is valid. After that it initializes the fdf struct and other
 * parameters, and calls the necessary functions to create the window and image
 * with the MLX42 library. It also handles the program's main loop and install
 * the necessary hooks to handle user input. 
 * 
 * @param argc The number of arguments passed to the program.
 * @param argv The arguments passed to the program as strings.
 * @return EXIT_SUCCESS when the program ends successfully.
 */
int	main(int argc, char **argv)
{
	t_fdf	fdf;

	parse_args_and_map(argc, argv, &fdf);
	fdf.parallel.pixels = read_map(argv[1], &fdf.map_info);
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	fdf.window = mlx_init(WIDTH, HEIGHT, argv[1], true);
	if (!fdf.window)
		handle_mlx_error(&fdf);
	fdf.image = mlx_new_image(fdf.window, WIDTH, HEIGHT);
	if (!fdf.image || (mlx_image_to_window(fdf.window, fdf.image, 0,
				0) < 0))
		handle_mlx_error(&fdf);
	init_camera_and_map_params(&fdf);
	apply_camera_params(&fdf.parallel, fdf.map_info, fdf.camera);
	init_map_projections(&fdf);
	mlx_loop_hook(fdf.window, draw_loop, &fdf);
	action_hooks(&fdf);
	mlx_loop(fdf.window);
	mlx_terminate(fdf.window);
	free_maps(&fdf);
	return (EXIT_SUCCESS);
}

/**
 * @brief The function that handles the main loop of the program. It is called
 * every time the window needs to be redrawn. It deletes the current image and
 * creates a new one, then calls the render_image function to draw the map on
 * the new image with the updated parameters.
 * 
 * @param param The fdf struct that contains all the necessary information to
 * draw the map.
 */
void	draw_loop(void *param)
{
	t_fdf	*fdf;

	fdf = param;
	mlx_delete_image(fdf->window, fdf->image);
	fdf->image = mlx_new_image(fdf->window, WIDTH, HEIGHT);
	mlx_image_to_window(fdf->window, fdf->image, 0, 0);
	render_image(fdf->current_map, fdf->map_info, fdf);
}

/**
 * @brief The function that installs the close_loop_hook, which is responsible
 * for closing the window when the users presses the ESC key
 * 
 * @param param The fdf struct that contains all the necessary information to
 * draw the map.
 */
void	action_hooks(void *param)
{
	t_fdf	*fdf;

	fdf = param;
	mlx_loop_hook(fdf->window, close_loop_hook, fdf);
}
