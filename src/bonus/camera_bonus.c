/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_camera_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 10:02:20 by pehenri2          #+#    #+#             */
/*   Updated: 2024/02/09 10:53:39 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

/**
 * @brief Sets the initial values of the camera, map and background parameters.
 * Gets the proportion of the map to fill the window, and  offsets and zoom of
 * the camera to centralize the image in the window. It also sets the initial
 * offsets of the map so that the (0,0) coordinate is at the middle of the image.
 * 
 * @param fdf Struct that contains all the necessary information to draw the
 * image on the window.
 */
void	init_camera_and_map_params(t_fdf *fdf)
{
	fdf->camera.proportion = get_map_proportion(fdf->map_info);
	fdf->camera.x_offset = WIDTH / 2;
	fdf->camera.y_offset = HEIGHT / 2;
	fdf->camera.zoom = 1;
	fdf->camera.x_angle = 0;
	fdf->camera.y_angle = 0;
	fdf->camera.z_angle = 0;
	fdf->map_info.x_offset = fdf->map_info.width / 2.0;
	fdf->map_info.y_offset = fdf->map_info.height / 2.0;
	fdf->map_info.background_color = 0x000000FF;
	fdf->parallel.x_offset_correction = 0;
	fdf->parallel.y_offset_correction = 0;
}

/**
 * @brief Calculates the width and height proportion between the map and the
 * window and returns the smallest one.
 * 
 * @param map_info The struct that contains the information about the map.
 * @return The proportion of the map to fit the window and the camera.
 */
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

/**
 * @brief Iterates through the pixel matrix and applies the proportion and
 * centralization to each pixel.
 * 
 * @param map The pixel matrix with the coordinates and color of each pixel.
 * @param map_info The struct that contains the information about the map.
 * @param cam The struct that contains the information about the camera.
 */
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

/**
 * @brief Applies the appropriate offsets to the coordinates of the
 * pixels in order to centralize the map, so that the  * (0,0)
 * coordinate is at the middle of the image.
 * 
 * @param pixel Struct that contains the coordinates and color of a pixel.
 * @param map_info Struct that contains the information about the map.
 */
void	centralize_pixel(t_pixel *pixel, t_map_info map_info)
{
	pixel->x_axis = pixel->x_axis - map_info.x_offset;
	pixel->y_axis = pixel->y_axis - map_info.y_offset;
	pixel->z_axis = pixel->z_axis - ((map_info.max_z - map_info.min_z) / 2);
}

/**
 * @brief Applies the proportion to the coordinates of the pixels, so that the
 * image fills the window.
 * 
 * @param pixel Struct that contains the coordinates and color of a pixel.
 * @param cam Struct that contains the information about the camera.
 */
void	apply_proportion(t_pixel *pixel, t_camera cam)
{
	pixel->x_axis = pixel->x_axis * cam.proportion;
	pixel->y_axis = pixel->y_axis * cam.proportion;
	pixel->z_axis = pixel->z_axis * cam.proportion;
}
