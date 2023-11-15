/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 10:02:20 by pehenri2          #+#    #+#             */
/*   Updated: 2023/11/15 08:57:18 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

//fazer centralize_pixel para depois ter uma função variadica que itera várias funções no mapa
void	centralize_map(t_map_info map_info, t_pixel **pixels)
{
	unsigned int	h;
	unsigned int	w;
	float			offset_x;
	float			offset_y;

	offset_x = map_info.width / 2.0;
	offset_y = map_info.height / 2.0;
	h = -1;
	while (++h < map_info.height)
	{
		w = -1;
		while (++w < map_info.width)
		{
			pixels[h][w].x_axis = pixels[h][w].x_axis - offset_x;
			pixels[h][w].y_axis = pixels[h][w].y_axis - offset_y;
			pixels[h][w].z_axis = pixels[h][w].z_axis - (
					(map_info.max_z - map_info.min_z) / 2.0);
		}
	}
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

void	init_camera_params(t_fdf *fdf)
{
	fdf->camera.proportion = get_map_proportion(*fdf);
	fdf->camera.x_offset = WIDTH / 2;
	fdf->camera.y_offset = HEIGHT / 2;
}

void	apply_camera_params(t_fdf *fdf)
{
	//centralize
	//apply proportion
}
