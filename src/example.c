/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   example.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 13:50:36 by pehenri2          #+#    #+#             */
/*   Updated: 2023/10/23 13:58:09 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// -----------------------------------------------------------------------------
// Codam Coding College, Amsterdam @ 2022-2023 by W2Wizard.
// See README in the root project for more information.
// -----------------------------------------------------------------------------

#include "fdf.h"
#include <MLX42/MLX42.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int32_t	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void	ft_randomize(mlx_image_t *image)
{
	uint32_t	i;
	uint32_t	y;
	uint32_t	color;

	i = 0;
	while (i < image->width)
	{
		y = 0;
		while (y < image->height)
		{
			color = ft_pixel(rand() % 0xFF, rand() % 0xFF, rand() % 0xFF, rand()
				% 0xFF);
			mlx_put_pixel(image, i, y, color);
			++y;
		}
		++i;
	}
}

// int32_t	main(int32_t argc, const char *argv[])
//{
//	mlx_t		*mlx;
//	mlx_image_t	*image;

//	mlx = mlx_init(WIDTH, HEIGHT, "fdf", true);
//	if (!mlx)
//	{
//		puts(mlx_strerror(mlx_errno));
//		return (EXIT_FAILURE);
//	}
//	image = mlx_new_image(mlx, 128, 128);
//	if (!image)
//	{
//		mlx_close_window(mlx);
//		puts(mlx_strerror(mlx_errno));
//		return (EXIT_FAILURE);
//	}
//	if (mlx_image_to_window(mlx, image, 0, 0) == -1)
//	{
//		mlx_close_window(mlx);
//		puts(mlx_strerror(mlx_errno));
//		return (EXIT_FAILURE);
//	}
//	mlx_loop_hook(mlx, ft_randomize, image);
//	mlx_loop(mlx);
//	mlx_terminate(mlx);
//	return (EXIT_SUCCESS);
//}
