/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projections_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 20:21:33 by pehenri2          #+#    #+#             */
/*   Updated: 2024/02/09 11:00:09 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

/**
 * @brief Creates the Oblique and isometric projections of the map and sets the
 * isometric as the current one. It copies the parallel projection to the
 * corresponding projection, pixel by pixel and then applies the appropriate
 * transformation to each pixel.
 * 
 * @param fdf Struct that contains all the necessary information about the map,
 */
void	init_map_projections(t_fdf *fdf)
{
	init_map(&fdf->oblique, *fdf);
	transform_map(&fdf->oblique, fdf, to_oblique);
	init_map(&fdf->isometric, *fdf);
	transform_map(&fdf->isometric, fdf, to_isometric);
	fdf->current_map = &fdf->isometric;
}

/**
 * @brief Copies the parallel projection to the projection passed as argument, 
 * pixel by pixel to later be transformed.
 * 
 * @param fdf Struct that contains all the necessary information about the map,
 */
void	init_map(t_map *map, t_fdf fdf)
{
	unsigned int	h;
	unsigned int	w;

	map->pixels = malloc(fdf.map_info.height * sizeof(t_pixel *));
	if (!map->pixels)
		handle_error("Error allocating memory");
	h = -1;
	while (++h < fdf.map_info.height)
	{
		map->pixels[h] = malloc(fdf.map_info.width * sizeof(t_pixel));
		if (!map->pixels[h])
			handle_error("Error allocating memory");
		w = -1;
		while (++w < fdf.map_info.width)
		{
			map->pixels[h][w] = fdf.parallel.pixels[h][w];
		}
	}
}

/**
 * @brief Transforms the map passed as the first argument using the function
 * passed as the last argument. It applies the function to each pixel of the
 * map and then refreshes the corner pixels of the map after the transformation.
 * Lastly, it sets the initial zoom and the offset correction for the map.
 * 
 * @param map Pointer to the map to be transformed.
 * @param fdf Struct that contains all the necessary information about the map,
 * the camera and the window.
 * @param func Function that will be applied to each pixel of the map.
 */
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

/**
 * @brief Set the initial zoom value for the map. It calculates the width and
 * height ratio between the window and the image and sets the smallest one as the
 * initial zoom so that the image fits the window perfectly after all the 
 * transformations.
 * 
 * @param map Pointer to the map to be zoomed.
 * @param zoom Pointer to the zoom value that will be set.
 */
void	set_initial_zoom(t_map *map, float *zoom)
{
	float			width_ratio;
	float			height_ratio;

	width_ratio = WIDTH / (float)(map->x_max - map->x_min);
	height_ratio = HEIGHT / (float)(map->y_max - map->y_min);
	*zoom = fminf(width_ratio, height_ratio) * 0.9;
}

/**
 * @brief Set the offset correction for the map. It calculates the average of the
 * maximum and minimum x and y values of the map after the transformations and 
 * sets it as the offset correction in order for the map to once again be
 * centered in the window.
 * 
 * @param map Pointer to the map to be corrected.
 */
void	set_map_offset_correction(t_map *map)
{
	float	new_x_offset;
	float	new_y_offset;

	new_x_offset = (map->x_max + map->x_min) / 2;
	new_y_offset = (map->y_max + map->y_min) / 2;
	map->x_offset_correction = new_x_offset;
	map->y_offset_correction = new_y_offset;
}
