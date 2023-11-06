/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 20:11:54 by pehenri2          #+#    #+#             */
/*   Updated: 2023/11/06 12:25:42 by pehenri2         ###   ########.fr       */
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
			printf("x[%d][%d]:%d ", h, w, pixels[h][w].x_axis);
			printf("y[%d][%d]:%d ", h, w, pixels[h][w].y_axis);
			printf("z[%d][%d]:%d ", h, w, pixels[h][w].z_axis);
			printf("\n");
			w++;
		}
		printf("\n");
		h++;
	}
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
			pixels[h][w] = to_isometric(pixels[h][w]);
			w++;
		}
		h++;
	}
}
