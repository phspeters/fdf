/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 17:50:41 by pehenri2          #+#    #+#             */
/*   Updated: 2024/02/09 16:38:31 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

/**
 * @brief Puts a pixel in the image with the given color at the given coordinates
 * but only if the coordinates are inside the window to avoid segmentation fault.
 * 
 * @param img The image where the pixel will be put.
 * @param x The x coordinate of the pixel.
 * @param y The y coordinate of the pixel.
 * @param color The color of the pixel.
 */
void	put_valid_pixel(mlx_image_t *img, int x, int y, uint32_t color)
{
	if ((x > 0 && x < WIDTH) && (y > 0 && y < HEIGHT))
		mlx_put_pixel(img, x, y, color);
}

/**
 * @brief Moves the given coordinate in the given direction.
 * Used in the Bresenham's line algorithm to move the x and y coordinates.
 * 
 * @param coordinate The coordinate to be moved.
 * @param direction The direction to move the coordinate.
 */
void	move_coordinate(int *coordinate, int direction)
{
	if (direction < 0)
		*coordinate -= 1;
	else
		*coordinate += 1;
}

/**
 * @brief Refreshes the maximum and minimum x and y coordinates of the map.
 * Called after the map transformations are applied.
 * 
 * @param pixel The pixel to be compared with the current maximum and minimum
 * coordinates.
 * @param map The map that contains the current maximum and minimum coordinates.
 */
void	refresh_corner_pixels(t_pixel pixel, t_map *map)
{
	if (pixel.x_axis > map->x_max)
		map->x_max = pixel.x_axis;
	if (pixel.x_axis < map->x_min)
		map->x_min = pixel.x_axis;
	if (pixel.y_axis > map->y_max)
		map->y_max = pixel.y_axis;
	if (pixel.y_axis < map->y_min)
		map->y_min = pixel.y_axis;
}

/**
 * @brief Refreshes the maximum and minimum z coordinates of the map.
 * Called while the map is being read.
 * 
 * @param z_axis The z coordinate to be compared with the current maximum and
 * minimum coordinates.
 * @param map_info The struct that contains the information about the map.
 */
void	refresh_min_and_max_z(int z_axis, t_map_info *map_info)
{
	if (z_axis > map_info->max_z)
		map_info->max_z = z_axis;
	if (z_axis < map_info->min_z)
		map_info->min_z = z_axis;
}

/**
 * @brief Frees the memory allocated for the maps pixel matrixes.
 * 
 * @param fdf The struct that contains the information about the maps and their
 * pixel matrix.
 */
void	free_maps(t_fdf *fdf)
{
	ft_free_ptr_array((void **)fdf->parallel.pixels, fdf->map_info.height);
	ft_free_ptr_array((void **)fdf->isometric.pixels, fdf->map_info.height);
	ft_free_ptr_array((void **)fdf->oblique.pixels, fdf->map_info.height);
}
