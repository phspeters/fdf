/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projections.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 20:21:33 by pehenri2          #+#    #+#             */
/*   Updated: 2023/11/15 08:26:36 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

//devolver o mapa?
//criar função que chama init_projection para cada projeção?
void	init_projection(t_fdf *fdf, t_pixel **map)
{
	unsigned int	h;
	unsigned int	w;

	map = malloc(fdf->map_info.height * sizeof(t_pixel *));
	h = -1;
	while (++h < fdf->map_info.height)
	{
		map[h] = malloc(fdf->map_info.height * sizeof(t_pixel));
		w = -1;
		while (++w < fdf->map_info.width)
		{
			map[h][w] = fdf->parallel.pixels[h][w];
		}
	}
}

t_pixel	to_isometric(t_pixel pixel)
{
	t_pixel	new_pixel;
	float	angle;

	angle = 30 * (M_PI / 180);
	new_pixel.x_axis = (pixel.x_axis - pixel.y_axis) * cos(angle);
	new_pixel.y_axis = (pixel.x_axis + pixel.y_axis) * sin(angle)
		- (pixel.z_axis);
	new_pixel.z_axis = pixel.z_axis;
	new_pixel.rgba_channel = pixel.rgba_channel;
	return (new_pixel);
}
