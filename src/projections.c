/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projections.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 20:21:33 by pehenri2          #+#    #+#             */
/*   Updated: 2023/11/14 20:21:39 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	init_projections(t_fdf *fdf)
{
	unsigned int	h;
	unsigned int	w;

	fdf->isometric_map.pixels = malloc(fdf->map_height * sizeof(t_pixel *));
	h = -1;
	while (++h < fdf->map_height)
	{
		fdf->isometric_map.pixels[h] = malloc(fdf->map_height * sizeof(t_pixel));
		w = -1;
		while (++w < fdf->map_width)
		{
			fdf->isometric_map.pixels[h][w] = fdf->parallel_map.pixels[h][w];
		}
	}
}
