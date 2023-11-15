/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 20:11:54 by pehenri2          #+#    #+#             */
/*   Updated: 2023/11/15 14:35:14 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	print_map(t_pixel **pixels, int height, int width)
{
	int	h;
	int	w;

	h = 0;
	while (h < height)
	{
		w = 0;
		while (w < width)
		{
			printf("x[%d][%d]:%f ", h, w, pixels[h][w].x_axis);
			printf("y[%d][%d]:%f ", h, w, pixels[h][w].y_axis);
			printf("z[%d][%d]:%f ", h, w, pixels[h][w].z_axis);
			printf("\n");
			w++;
		}
		printf("\n");
		h++;
	}
}

void	print_pixel(t_pixel pixel)
{
	printf("x_axis: %f\n", pixel.x_axis);
	printf("y_axis: %f\n", pixel.y_axis);
	printf("z_axis: %f\n", pixel.z_axis);
	printf("rgba_channel: %u\n", pixel.rgba_channel);
}

void	map_to_iso(t_pixel **pixels, int height, int width)
{
	int	h;
	int	w;

	h = 0;
	while (h < height)
	{
		w = 0;
		while (w < width)
		{
			to_isometric(&pixels[h][w]);
			w++;
		}
		h++;
	}
}
