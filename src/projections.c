/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projections.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 20:21:33 by pehenri2          #+#    #+#             */
/*   Updated: 2023/11/16 17:54:29 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	init_map(t_pixel ***map, t_fdf fdf)
{
	unsigned int	h;
	unsigned int	w;

	*map = malloc(fdf.map_info.height * sizeof(t_pixel *));
	h = -1;
	while (++h < fdf.map_info.height)
	{
		(*map)[h] = malloc(fdf.map_info.width * sizeof(t_pixel));
		w = -1;
		while (++w < fdf.map_info.width)
		{
			(*map)[h][w] = fdf.parallel.pixels[h][w];
		}
	}
}

void	to_isometric(t_pixel *pixel)
{
	rotate_around_z_axis(pixel, -45);
	rotate_around_x_axis(pixel, 54);
}

void	set_initial_zoom(t_map *map, float *zoom)
{
	float			width_ratio;
	float			height_ratio;

	width_ratio = WIDTH / (float)(map->x_max - map->x_min);
	height_ratio = HEIGHT / (float)(map->y_max - map->y_min);
	*zoom = fminf(width_ratio, height_ratio);
}

void	transform_map(t_map *map, t_fdf *fdf, void (*func)(t_pixel *))
{
	unsigned int	h;
	unsigned int	w;

	map->x_max = INT_MIN;
	map->x_min = INT_MAX;
	map->y_max = INT_MIN;
	map->y_min = INT_MAX;
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
}

void	init_projections(t_fdf *fdf)
{
	init_camera_and_map_params(fdf);
	apply_camera_params(&fdf->parallel, fdf->map_info, fdf->camera);
	init_map(&fdf->isometric.pixels, *fdf);
	transform_map(&fdf->isometric, fdf, to_isometric);
	fdf->current_map = &fdf->isometric;
}
