/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 10:02:20 by pehenri2          #+#    #+#             */
/*   Updated: 2023/11/19 21:28:41 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

int	get_map_proportion(t_map_info map_info)
{
	float	width_distance;
	float	height_distance;
	int		proportion;

	width_distance = (WIDTH / (float)map_info.width);
	height_distance = (HEIGHT / (float)map_info.height);
	proportion = fminf(width_distance, height_distance) * 0.9;
	return (proportion);
}

void	init_camera_and_map_params(t_fdf *fdf)
{
	fdf->camera.proportion = get_map_proportion(fdf->map_info);
	fdf->camera.x_offset = WIDTH / 2;
	fdf->camera.y_offset = HEIGHT / 2;
	fdf->camera.zoom = 1;
	fdf->camera.x_angle = 0;
	fdf->camera.y_angle = 0;
	fdf->camera.z_angle = 0;
	fdf->camera.z_scale = 1;
	fdf->map_info.x_offset = fdf->map_info.width / 2.0;
	fdf->map_info.y_offset = fdf->map_info.height / 2.0;
}

void	apply_proportion(t_pixel *pixel, t_camera cam)
{
	pixel->x_axis = pixel->x_axis * cam.proportion;
	pixel->y_axis = pixel->y_axis * cam.proportion;
	pixel->z_axis = pixel->z_axis * cam.proportion * cam.z_scale;
}

void	centralize_pixel(t_pixel *pixel, t_map_info map_info)
{
	pixel->x_axis = pixel->x_axis - map_info.x_offset;
	pixel->y_axis = pixel->y_axis - map_info.y_offset;
	pixel->z_axis = pixel->z_axis - ((map_info.max_z - map_info.min_z) / 2);
}

void	apply_camera_params(t_map *map, t_map_info map_info, t_camera cam)
{
	unsigned int	h;
	unsigned int	w;

	h = -1;
	while (++h < map_info.height)
	{
		w = -1;
		while (++w < map_info.width)
		{
			centralize_pixel(&map->pixels[h][w], map_info);
			apply_proportion(&map->pixels[h][w], cam);
		}
	}
}
