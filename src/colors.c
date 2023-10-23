/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 13:51:03 by pehenri2          #+#    #+#             */
/*   Updated: 2023/10/18 14:14:52 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"

// Bytes Per Pixel. Since each pixel is represented as an integer, it will be
// four bytes for four channels.

// 'Encodes' four individual bytes into an int.
int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

// Get the red channel.
// Move 3 bytes to the right and mask out the first byte.
int	get_r(int rgba)
{
	return ((rgba >> 24) & 0xFF);
}

// Get the green channel.
// Move 2 bytes to the right and mask out the first byte.
int	get_g(int rgba)
{
	return ((rgba >> 16) & 0xFF);
}

// Get the blue channel.
// Move 1 byte to the right and mask out the first byte.
int	get_b(int rgba)
{
	return ((rgba >> 8) & 0xFF);
}

// Get the alpha channel.
// Move 0 bytes to the right and mask out the first byte.
int	get_a(int rgba)
{
	return (rgba & 0xFF);
}

/*************************** EXAMPLE ******************************
int32_t	main(void)
{
	// Init mlx with a canvas size of 256x256 and the ability to resize the window.
	mlx_t* mlx = mlx_init(256, 256, "MLX42", true);
	if (!mlx) exit(EXIT_FAILURE);
	// Create a 128x128 image.
	mlx_image_t* img = mlx_new_image(mlx, 128, 128);
	// Set the channels of each pixel in our image to the maximum byte value of 255.
	memset(img->pixels, 255, img->width * img->height * BPP);
	// Draw the image at coordinate (0, 0).
	mlx_image_to_window(mlx, img, 0, 0);
	// Run the main loop and terminate on quit.
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
*/