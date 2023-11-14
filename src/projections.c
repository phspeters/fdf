/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projections.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 19:08:55 by pehenri2          #+#    #+#             */
/*   Updated: 2023/11/14 19:17:17 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	init_projections(t_fdf *fdf)
{
	unsigned int	h;
	unsigned int	w;

	fdf->projections.isometric.pixels = malloc(fdf->projections.map_height * sizeof(t_pixel *));
	h = -1;
	while (++h < fdf->projections.map_height)
	{
		fdf->projections.isometric.pixels[h] = malloc(fdf->projections.map_height * sizeof(t_pixel));
		w = -1;
		while (++w < fdf->projections.map_width)
		{
			fdf->projections.isometric.pixels[h][w] = fdf->projections.parallel.pixels[h][w];
		}
	}
}
