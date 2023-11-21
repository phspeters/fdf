/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projections.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 20:21:33 by pehenri2          #+#    #+#             */
/*   Updated: 2023/11/17 19:03:41 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	set_map_offset_correction(t_map *map)
{
	float	new_x_offset;
	float	new_y_offset;

	new_x_offset = (map->x_max + map->x_min) / 2;
	new_y_offset = (map->y_max + map->y_min) / 2;
	map->x_offset_correction = new_x_offset;
	map->y_offset_correction = new_y_offset;
}

void	set_initial_zoom(t_map *map, float *zoom)
{
	float			width_ratio;
	float			height_ratio;

	width_ratio = WIDTH / (float)(map->x_max - map->x_min);
	height_ratio = HEIGHT / (float)(map->y_max - map->y_min);
	*zoom = fminf(width_ratio, height_ratio) * 0.9;
}

void	transform_map(t_map *map, t_fdf *fdf, void (*func)(t_pixel *))
{
	unsigned int	h;
	unsigned int	w;

	map->x_max = __FLT_MIN__;
	map->x_min = __FLT_MAX__;
	map->y_max = __FLT_MIN__;
	map->y_min = __FLT_MAX__;
	h = -1;
	while (++h < fdf->map_info.height)
	{
		w = -1;
		while (++w < fdf->map_info.width)
		{
			(*func)(&map->pixels[h][w]);
			refresh_corner_pixels(map->pixels[h][w], map);
		}
	}
	set_initial_zoom(map, &fdf->camera.zoom);
	set_map_offset_correction(map);
}

void	init_map(t_map *map, t_fdf fdf)
{
	unsigned int	h;
	unsigned int	w;

	map->pixels = malloc(fdf.map_info.height * sizeof(t_pixel *));
	h = -1;
	while (++h < fdf.map_info.height)
	{
		map->pixels[h] = malloc(fdf.map_info.width * sizeof(t_pixel));
		w = -1;
		while (++w < fdf.map_info.width)
		{
			map->pixels[h][w] = fdf.parallel.pixels[h][w];
		}
	}
}

void	init_projections(t_fdf *fdf)
{
	init_camera_and_map_params(fdf);
	apply_camera_params(&fdf->parallel, fdf->map_info, fdf->camera);
	init_map(&fdf->isometric, *fdf);
	transform_map(&fdf->isometric, fdf, to_isometric);
	fdf->current_map = &fdf->isometric;
}
