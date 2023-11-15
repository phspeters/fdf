/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 10:02:20 by pehenri2          #+#    #+#             */
/*   Updated: 2023/11/14 22:16:43 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	centralize_map(t_map_info map_info, t_pixel **pixels)
{
	unsigned int	h;
	unsigned int	w;
	float			offset_x;
	float			offset_y;

	offset_x = (map_info.width - 1) / 2.0;
	offset_y = (map_info.height - 1) / 2.0;
	pixels[h][w].x_axis = pixels[h][w].x_axis - offset_x;
	pixels[h][w].y_axis = pixels[h][w].y_axis - offset_y;
	pixels[h][w].z_axis = pixels[h][w].z_axis - ((map_info.max_z - map_info.min_z) / 2.0);
}

int	get_map_proportion(t_fdf fdf)
{
	float	width_distance;
	float	height_distance;
	int		proportion;

	width_distance = (WIDTH / (float)fdf.map_info.width);
	height_distance = (HEIGHT / (float)fdf.map_info.height);
	proportion = fminf(width_distance, height_distance) * 0.9;
	return (proportion);
}

void	init_camera(t_fdf *fdf)
{
	fdf->camera.proportion = get_map_proportion(*fdf);
	fdf->camera.x_offset = WIDTH / 2;
	fdf->camera.y_offset = HEIGHT / 2;
}
